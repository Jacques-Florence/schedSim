/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "actionValuesRecord.h"

#include <iostream>
#include <algorithm>
#include <cassert>
#include <memory>
#include <fstream>

#include <mdp/mdpConfiguration.h>

using namespace Mdp;

ActionValuesRecord::ActionValuesRecord(std::shared_ptr<MdpConfiguration> c,
                                       size_t stateSize,
                                       size_t actionSize)
	: conf(c)
	, S(stateSize)
	, A(actionSize)
{
}

void ActionValuesRecord::init()
{
	enableRecordingOfActionValues = conf->getBoolValue("reinforcementLearning", "recordActionValues", false);
	if (!enableRecordingOfActionValues)
		return;
	statesToRecord = getListOfActionsToRecordFromFile();
	chunkSize = conf->getIntValue("reinforcementLearning", "actionValueRecordChunkSize");
	assert(statesToRecord.size() > 0);
	assert(chunkSize > 0);
	std::cout << "S is "<<S <<"\n";
	std::cout << "A is "<< A <<"\n";
	std::cout << "chunkSize is " << chunkSize <<"\n";
	avChunk = std::vector<std::vector<std::vector<std::pair<double, double>>>>(S,
		std::vector<std::vector<std::pair<double, double>>>(A,
			std::vector<std::pair<double, double>>(chunkSize, std::pair<double, double>(NAN, NAN))));
	recordOnlyLastAction = conf->getBoolValue("reinforcementLearning", "recordOnlyLastAction", true);
	lastValueRecorded = std::vector<std::vector<double>>(S, std::vector<double>(A, NAN));
}



void ActionValuesRecord::end()
{
	/*if recording only last value, we need to write a datapoint at the end,
	otherwise the curve on the graph stops in the middle of the figure
	instead of going to the end*/
	if (!enableRecordingOfActionValues)
		return;
	if (recordOnlyLastAction)
		recordLastDataPoint();
	writeAllChunksToDisk();
}

void ActionValuesRecord::recordActionValues(ActionValuesFunction *actionValues,
                                            state_t state,
                                            action_t action)
{
	/*NOTE: enabling this consumes a LOT of resources*/
	if (!enableRecordingOfActionValues)
		return;
	assert(statesToRecord.size() > 0);
	if (recordOnlyLastAction)
		recordLastActionValue(actionValues->getValue(state, action), state, action);
	else
		recordAllActionValues(actionValues);
}

void ActionValuesRecord::recordAllActionValues(ActionValuesFunction *actionValues)
{
	if (!enableRecordingOfActionValues)
		return;
	/*For the moment, the avChunk contains all actions.
	And we only write to file those that are in the actionsToRecord.
	But maybe we should not even put in avRecord those actions that we don't want.*/
	static long long unsigned int index = 0;
	for (size_t s = 0; s < S; s++)
	{
		for (size_t a = 0; a < A; a++)
		{
			avChunk[s][a][index] = std::pair<double, double>(NAN, actionValues->getValue(s, a));
		}
	}
	index++;
	if (index == chunkSize)
	{
		writeAllChunksToDisk();
		index = 0;
	}
}

void ActionValuesRecord::recordLastActionValue(double value, state_t s, action_t a)
{
	if (!enableRecordingOfActionValues)
		return;
	static std::vector<std::vector<unsigned long long int>> indexes = std::vector<std::vector<unsigned long long int>>(
		S, std::vector<unsigned long long int>(A, 0));
	static unsigned long long int counter = 0;
	unsigned long long int index = indexes[s][a]++;
	avChunk[s][a][index] = std::pair<double, double>(counter, value);
	if (indexes[s][a] == chunkSize)
	{
		indexes[s][a] = 0;
		writeChunkToDisk(s, a);
	}
	lastValueRecorded[s][a] = value;
	counter++;
}

std::vector<int> ActionValuesRecord::getListOfActionsToRecordFromFile()
{
	std::vector<std::string> str = conf->getStringList("reinforcementLearning", "actionValuesRecorded");
	std::vector<int> states;
	for (size_t i = 0; i < str.size(); i++)
	{
		states.push_back(std::stoi(str[i]));
	}
	std::sort(states.begin(), states.end());
	return states;
}

void ActionValuesRecord::writeAllChunksToDisk()
{
	if (!enableRecordingOfActionValues)
		return;
	for (size_t s = 0; s < S; s++)
	{
		for (size_t a = 0; a < A; a++)
		{
			writeChunkToDisk(s, a);
		}
	}
}

void ActionValuesRecord::writeChunkToDisk(state_t s, action_t a)
{
	if (!enableRecordingOfActionValues)
		return;
	if (std::find(statesToRecord.begin(), statesToRecord.end(), s) == statesToRecord.end())
		return;
	std::string filename = conf->getFilePrefix() + "actionValuesForState";
	filename += std::to_string(s) + "action" + std::to_string(a);
	std::cerr << "writing chunk to "<< filename<<" \n";
	std::ofstream file;
	file.open(filename, std::ios_base::app);
	int counter = 0;
	for (size_t index = 0; index < avChunk[s][a].size(); index++)
	{
		if (std::isnan(avChunk[s][a][index].second))
			break;
		if (counter == 5)
		{
			counter = 0;
			
		counter++;
		if (!std::isnan(avChunk[s][a][index].first)) //maybe there's a better way, like putting the if out of loop
			file << avChunk[s][a][index].first << " ";
		file << avChunk[s][a][index].second << "\n";
		}
		counter++;
	}
	file.close();
	/*at this point, the chunk contains the previous values. Let's update it to contain only one value: the last one*/
	for (size_t index = 0; index < chunkSize; index++)
	{
		avChunk[s][a][index] = avChunk[s][a][chunkSize-1]; /*TODO optimize...*/
	}
}



void ActionValuesRecord::recordLastDataPoint()
{
	if (!enableRecordingOfActionValues)
		return;
	for (size_t i = 0; i < statesToRecord.size(); i++)
	{
		state_t s = statesToRecord[i];
		for (action_t a = 0; a < A; a++)
		{
			if (s >= lastValueRecorded.size())
			{
				std::cerr << "s is " << s <<"\n";
				std::cerr << "size of vector: " << lastValueRecorded.size() <<"\n";
				throw std::invalid_argument("invalid state to record");
			}
			recordLastActionValue(lastValueRecorded[s][a], s, a);
		}
	}
}





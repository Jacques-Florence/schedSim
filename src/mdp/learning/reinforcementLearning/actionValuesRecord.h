/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef ACTION_VALUES_RECORD_H
#define ACTION_VALUES_RECORD_H

#include <cmath>
#include <cstddef>
#include <memory>
#include <vector>

#include <mdp/stateSpace.h>
#include <mdp/actionSpace.h>
#include <mdp/learning/reinforcementLearning/actionValuesFunction/actionValuesFunction.h>

namespace Mdp
{

class MdpConfiguration;

class ActionValuesRecord
{
public:
	ActionValuesRecord(std::shared_ptr<MdpConfiguration> conf, size_t stateSize, size_t actionSize);
	void init();
	void recordActionValues(ActionValuesFunction *actionValues, state_t state, action_t action);
	void end();
private:
	void recordAllActionValues(ActionValuesFunction *actionValues);
	void recordLastActionValue(double value, state_t state, action_t action);
	std::vector<int> getListOfActionsToRecordFromFile();
	void writeChunkToDisk(state_t s, action_t a);
	void writeAllChunksToDisk();
	/*order: state, actions, chunk*/
	std::vector<std::vector<std::vector<std::pair<double, double>>>> avChunk;
	std::shared_ptr<MdpConfiguration> conf;
	std::vector<int> statesToRecord;
	size_t chunkSize;
	size_t S;
	size_t A;
	bool enableRecordingOfActionValues{false};
	bool recordOnlyLastAction{false};
	void recordLastDataPoint();
	std::vector<std::vector<double>> lastValueRecorded;
};


}
#endif

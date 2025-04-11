#ifndef __CA_TRANSACTION__
#define __CA_TRANSACTION__

#include <map>
#include <memory>
#include <thread>
#include <vector>
#include <regex>

#include "ca/global.h"
#include "ca/txhelper.h"
#include "ca/block_stroage.h"
#include "ca/block_monitor.h"
#include "ca/vrf_consensus.h"

#include "net/msg_queue.h"
#include "net/interface.h"

#include "utils/cycliclist.hpp"

#include "proto/block.pb.h"
#include "proto/transaction.pb.h"
#include "proto/block.pb.h"
#include "proto/ca_protomsg.pb.h"
#include "proto/interface.pb.h"
#include "mpt/trie.h"

/**
 * @brief       Get the Balance By Utxo object
 * 
 * @param       address: 
 * @param       balance: 
 * @return      int 
 */
int GetBalanceByUtxo(const std::string & address, const std::string & assetType, uint64_t &balance);

typedef enum emTransactionType{
	kTransactionType_Unknown = -1,	// Unknown
	kTransactionType_Genesis = 0, 	// Genesis Deal
	kTransactionType_Tx,			// Normal trading
} TransactionType;

/**
 * @brief       Get the Transaction Type object
 * 
 * @param       tx: 
 * @return      TransactionType 
 */
TransactionType GetTransactionType(const CTransaction & tx);

/**
 * @brief       Receive transaction flow information
 * 
 * @param       msg: 
 * @param       msgData: 
 * @return      int 
 */
int HandleTx( const std::shared_ptr<TxMsgReq>& msg, const MsgData& msgData);
/**
 * @brief       Deal with contract transaction flow
 * 
 * @param       msg: 
 * @param       msgData: 
 * @return      int 
 */
int HandleContractTx( const std::shared_ptr<ContractTxMsgReq>& msg, const MsgData& msgData);
/**
 * @brief       Handle transaction flow
 * 
 * @param       msg: 
 * @param       outTx: 
 * @return      int 
 */
int DoHandleTx( const std::shared_ptr<TxMsgReq>& msg, CTransaction & outTx);
/**
 * @brief       Receive block flow information
 * 
 * @param       msg: 
 * @param       msgData: 
 * @return      int 
 */
int HandleBlock(const std::shared_ptr<BlockMsg>& msg, const MsgData& msgData);

/**
 * @brief       Adding block signatures
 * 
 * @param       block: 
 * @return      int 
 */
int AddBlockSign(CBlock &block);

/**
 * @brief       Verifying block signature
 * 
 * @param       block: 
 * @return      int 
 */
int VerifyBlockSign(const CBlock &block);
/**
 * @brief       Handle block flows
 * 
 * @param       msg: 
 * @return      int 
 */
int DoHandleBlock(const std::shared_ptr<BlockMsg>& msg, Node *node = nullptr);
/**
 * @brief       Processing block broadcast information
 * 
 * @param       msg: 
 * @param       msgData: 
 * @return      int 
 */
int HandleBuildBlockBroadcastMsg( const std::shared_ptr<BuildBlockBroadcastMsg>& msg, const MsgData& msgData);
/**
 * @brief       Find multiple signing nodes
 * 
 * @param       tx: 
 * @param       msg: 
 * @param       nextNodes: 
 * @return      int 
 */
int FindSignNode(const CTransaction & tx, const std::shared_ptr<TxMsgReq> &msg, std::unordered_set<std::string> & nextNodes, const uint64_t& buildBlockHeight);

/**
 * @brief       The data source of the vrf is obtained by time
 * 
 * @param       txTime: 
 * @param       txHeight: 
 * @param       txHash: 
 * @param       targetAddrs:
 * @return      int 
 */
int GetVrfDataSourceByTime(const uint64_t& txTime, const uint64_t& txHeight, std::string &txHash, std::vector<std::string>& targetAddrs);
/**
 * @brief       Calculate the packager by time
 * 
 * @param       txTime: 
 * @param       txHeight: 
 * @param       packager: 
 * @param       proof:
 * @param       txHash:
 * @return      int 
 */
int CalculateThePackerByTime(const uint64_t& txTime, std::string& packager);
/**
 * @brief       Get the contract block packager
 * 
 * @param       txTime: 
 * @param       txHeight: 
 * @param       packager: 
 * @param       info:
 * @return      int 
 */
int GetContractDistributionManager(const uint64_t& txTime, std::string& packager);
/**
 * @brief       Contract packager validation
 * 
 * @param       tx: 
 * @param       height: 
 * @param       vrfInfo: 
 * @return      int 
 */
int VerifyContractDistributionManager(const CTransaction& tx);
/**
 * @brief       Find the pledged amount through the pledged address
 * 
 * @param       address: 
 * @param       stakeamount: 
 * @param       stakeType: 
 * @return      int 
 */
int SearchStake(const std::string &address, uint64_t &stakeamount,  global::ca::StakeType stakeType);
/**
 * @brief       Whether the transaction is issued by itself
 * 
 * @param       tx: 
 * @return      TxHelper::vrfAgentType 
 */
TxHelper::vrfAgentType IsNeedAgent(const CTransaction & tx);


/**
 * @brief       Whether the current address meets the qualification of depledging
 * 
 * @param       fromAddr: 
 * @param       utxoHash: 
 * @param       stakedAmount: 
 * @return      int 
 */
int IsQualifiedToUnstake(const std::string& fromAddr, const std::string& utxoHash, uint64_t& stakedAmount, const std::string& assetType);
int IsQualifiedToUnLock(const std::string& fromAddr, const std::string& utxoHash, uint64_t& lockedAmount, const std::string& assetType);
// int IsQualifiedToLock(const std::string& fromAddr, const std::string& utxoHash, uint64_t& lockedAmount, const std::string& assetType);
/**
 * @brief       Check whether the investment qualification is met
 * 
 * @param       fromAddr: 
 * @param       toAddr: 
 * @param       investAmount: 
 * @return      int 
 */
// int CheckInvestQualification(const std::string& fromAddr, 
// 						const std::string& toAddr, uint64_t investAmount);
int CheckInvestQualification(const std::string& fromAddr, 
                        const std::string& toAddr, const std::string& assetType, uint64_t investAmount);
/**
 * @brief       Check if the bonus qualification is met
 * 
 * @param       BonusAddr: 
 * @param       txTime: 
 * @param       verifyAbnormal: 
 * @return      int 
 */
int CheckBonusQualification(const std::string& BonusAddr, const uint64_t& txTime, bool verifyAbnormal = true);


int CheckTreasuryQualificationAndGetRewardAmount(const std::string& TreasuryAddr, const uint64_t& txTime, bool verifyAbnormal = true);

/**
 * @brief       Whether the solution investment qualification is met
 * 
 * @param       fromAddr: 
 * @param       toAddr: 
 * @param       utxoHash: 
 * @param       investedAmount: 
 * @return      int 
 */
int IsQualifiedToDisinvest(const std::string& fromAddr, const std::string &assetType, const std::string& toAddr,
						const std::string& utxoHash, uint64_t& investedAmount);

/**
 * @brief       Verify that the transaction has timed out
 * 
 * @param       tx: 
 * @return      int 
 */
int VerifyTxTimeOut(const CTransaction &tx);

/**
 * @brief
 * 
 * @param       tx: 
 * @return      int 
 */
int VerifyTxUtxoHeight(const CTransaction &tx, const uint64_t& txUtxoHeight);

/**
 * @brief       Check time of the unstake, unstake time must be more than 30 days
 * 
 * @param       utxo: 
 * @return      true 
 * @return      false 
 */
bool IsMoreThan30DaysForUnstake(const std::string& utxo);

/**
 * @brief       Check time of the redeem, redeem time must be more than 30 days,
 * 
 * @param       utxo: 
 * @return      true 
 * @return      false 
 */
bool IsMoreThan1DayForDivest(const std::string& utxo);
/**
 * @brief       Verify the Bonus Addr
 * 
 * @param       BonusAddr: 
 * @return      int 
 */
int VerifyBonusAddr(const std::string & BonusAddr);
/**
 * @brief       Get the Investment Amount And Duration object
 * 
 * @param       bonusAddr: 
 * @param       curTime: 
 * @param       zeroTime: 
 * @param       mpInvestAddr2Amount: 
 * @return      int 
 */
int GetInvestmentAmountAndDuration(const std::string & bonusAddr,const uint64_t &curTime,const uint64_t &zeroTime,std::multimap<std::string, std::pair<uint64_t,uint64_t>> &mpInvestAddr2Amount);
/**
 * @brief       Get the Total Circulation Yesterday object
 * 
 * @param       curTime: 
 * @param       totalCirculation: 
 * @return      int 
 */
int GetTotalCirculationYesterday(const uint64_t &curTime, uint64_t &totalCirculation);
/**
 * @brief       Get the Total Investment Yesterday object
 * 
 * @param       curTime: 
 * @param       totalinvest: 
 * @return      int 
 */
int GetTotalInvestmentYesterday(const uint64_t &curTime, uint64_t &totalinvest);
/**
 * @brief       Get the Total Burn Yesterday object
 * 
 * @param       curTime: 
 * @param       TotalBrun: 
 * @return      int 
 */
int GetTotalBurnYesterday(const uint64_t &curTime, uint64_t &TotalBrun);

/**
 * @brief       Notify the node of the height change
 * 
 */
void NotifyNodeHeightChange();

/**
 * @brief       Validate the transaction information request
 * 
 * @param       msg: 
 * @return      int 
 */
int VerifyTxMsgReq(const TxMsgReq & msg);

/**
 * @brief       
 * 
 * @param       txMsg: 
 * @param       tx: 
 * @return      int 
 */
int DropshippingTx(const std::shared_ptr<TxMsgReq> & txMsg,const CTransaction &tx);

/**
 * @brief       
 * 
 * @param       txMsg: 
 * @param       tx: 
 * @param       addr:
 * @return      int 
 */
int DropshippingTx(const std::shared_ptr<TxMsgReq> &txMsg, const CTransaction &tx, const std::string& addr);
/**
 * @brief       
 * 
 * @param       txMsg: 
 * @param       tx: 
 * @return      int 
 */
int DropCallShippingTx(const std::shared_ptr<ContractTxMsgReq> & txMsg,const CTransaction &tx);

/**
 * @brief       Calculate Gas
 * 
 * @param       tx: 
 * @param       gas: 
 * @return      int 
 */
int CalculateGas(const CTxUtxos &utxo,const std::string & txType, const uint64_t gasSize, uint64_t &gas);

/**
 * @brief       Generate Gas
 * 
 * @param       tx: 
 * @param       voutSize: 
 * @param       gas: 
 * @return      int 
 */
int GenerateGas(const CTxUtxos &utxo, const std::string & txType, const uint64_t voutSize, const uint64_t gasSize,uint64_t &gas);
int PrecalculatedGas(const CTransaction &tx, const uint64_t voutSize, uint64_t &gas);

/**
 * @brief       Verify that the vrf data source is correct
 * 
 * @param       tx: 
 * @return      int 
 */
bool CheckTxConsensusStatus(const CTransaction &tx);
/**
 * @brief       Get the contract root hash
 * 
 * @param       contractAddress:
 * @param       rootHash: 
 * @param		contractDataCache:
 * @return      int 
 */
int GetContractRootHash(const std::string& contractAddress, std::string& rootHash, ContractDataCache* contractDataCache);

/**
 * @brief       Determines if the current block is a contract block
 * 
 * @param       block: 
 * @return      return
 * @return		false
 */
bool IsContractBlock(const CBlock & block);
/**
 * @brief       Calculate Pack Node
 * 
 * @param       seed:
 * @param       targetAddrs: 
 * @return      string
 */
static std::string CalculatePackNode(const std::string seed, const std::vector<std::string> &targetAddrs);
/**
 * @brief       Find the contract packaging node
 * 
 * @param       txHash:
 * @param       utcTime: 
 * @param       targetAddr: 
 * @return      int
 */
int FindContractPackNode(const std::string & txHash, const uint64_t& utcTime, std::string &targetAddr);
/**
 * @brief       Verify the contract packaging node
 * 
 * @param       dispatchNodeAddr:
 * @param       randNum: 
 * @param       targetAddr: 
 * @param       _vrfNodelist: 
 * @return      int
 */
int VerifyContractPackNode(const std::string& seed, const uint64_t& time, const std::string& targetAddr);

/**
 * @brief       Get Contract Addr
 * 
 * @param       tx: tx
 * @return      std::string Contract Addr
 */
std::string GetContractAddr(const CTransaction & tx);
std::set<std::string> GetcontractPreHash(const CBlock & block);

uint64_t getStake(const std::string& addr);

int GetStakeAmountByTime(const std::string& address, const uint64_t& time, uint64_t& total);
int GetInvestAmountByTime(const std::string& address, const uint64_t& time, uint64_t& investAmount);
int64_t GetStakeInvestAmountByTime(const std::string& addr, const uint64_t& time);

template<typename RandomEngine>
void shuffleInput(std::vector<std::pair<std::string, VRFStructure>>& input, RandomEngine& engine);

std::vector<std::string> randomlySelectElements(std::vector<std::pair<std::string, VRFStructure>>& input, int numSelections, std::string seed);
int FindValidationNodes(const uint64_t& blockTime, const std::string &addr, std::vector<std::string>& validationAddrs);
int SearchNodeToSendMsg(BlockMsg &msg, const CBlock& cblock);
int VerifyBlockSignatureNodeSelection(const uint64_t& blockTime, const std::string& packagerAddress, const std::vector<std::string>& getValidationAddrs);
std::vector<std::pair<std::string, VRFStructure>> shuffleMap(const std::map<std::string, VRFStructure>& original_map, const std::string& seed);

int GetBlockPackager(std::string &packager, const std::string & txData, const uint64_t txTime);
int VerifyBlockPackager(const CTransaction& tx);
int VerifyValidNode(const std::string &addr);

template <typename T>
std::vector<T> getRandomElements(const std::vector<T>& vec, size_t numElements) {
    if (numElements > vec.size()) {
        numElements = vec.size();
    }

    std::vector<size_t> indices(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        indices[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(indices.begin(), indices.end(), gen);

    std::vector<T> randomElements;
    randomElements.reserve(numElements);
    for (size_t i = 0; i < numElements; ++i) {
        randomElements.push_back(vec[indices[i]]);
    }
    return randomElements;
}

std::string GetPackager(const CBlock & block);

int HandleCheckContractPreHashReq(const std::shared_ptr<CheckContractPreHashReq> &msg, const MsgData &msgData);
int HandleCheckContractPreHashAck(const std::shared_ptr<CheckContractPreHashAck> &msg, const MsgData &msgData);

#endif

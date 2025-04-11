
#ifndef _RPC_CREATE_TRANSACTION_H_
#define _RPC_CREATE_TRANSACTION_H_

#include "ca/txhelper.h"
#include "rpc_tx.h"
#include <cstdint>

/**
    * @brief       
    * 
    * @param       fromAddr: 
    * @param       toAddr: 
    * @param       ack: 
    * @return      
    */

void ReplaceCreateTxTransaction(const std::vector<TxHelper::Memechain> txAsset,const std::pair<std::string,std::string>& gastrade,
                                bool isGastrade, bool isFindUtxo, const std::string& encodedInfo, txAck * ack);

/**
    * @brief       
    * 
    * @param       fromAddr: 
    * @param       stakeAmount: 
    * @param       pledgeType: 
    * @param       ack: 
    * @return      
    */

void ReplaceCreateStakeTransaction(const std::string & fromAddr, uint64_t stakeAmount,  int32_t pledgeType,const std::pair<std::string,std::string>& gastrade,
                                bool isGastrade, txAck* ack, double commissionRate, bool isFindUtxo, const std::string& encodedInfo);
/**
    * @brief       
    * 
    * @param       fromAddr: 
    * @param       utxoHash: 
    * @param       ack: 
    * @return      std::string 
    */


void ReplaceCreateUnstakeTransaction(const std::string& fromAddr, const std::string& utxoHash,const std::pair<std::string,std::string>& gastrade,
                                                        bool isGastrade, bool isFindUtxo, const std::string& encodedInfo, txAck* ack);
/**
    * @brief       
    * 
    * @param       fromAddr: 
    * @param       toAddr: 
    * @param       investAmount: 
    * @param       investType: 
    * @param       ack: 
    * @return     
    */
void ReplaceCreateInvestTransaction(const std::string & fromAddr,const std::string assetType, const std::string& toAddr,
					uint64_t investAmount, int32_t investType,const std::pair<std::string,std::string>& gastrade,bool isGastrade, bool isFindUtxo, const std::string& encodedInfo, txAck* ack);

/**
    * @brief       
    * 
    * @param       fromAddr: 
    * @param       toAddr: 
    * @param       utxoHash: 
    * @param       ack: 
    * @return      
    */

void ReplaceCreateDisinvestTransaction(const std::string& fromAddr,const std::string &assetType, const std::string& toAddr, const std::string& utxoHash,
                        const std::pair<std::string,std::string>& gastrade,bool isGastrade, bool isFindUtxo, const std::string& encodedInfo, txAck* ack);

/**
    * @brief       
    * 
    * @param       Addr: 
    * @param       ack: 
    * @return      
    */
void ReplaceCreateBonusTransaction(const std::string &addr, std::string assetType, std::pair<std::string, std::string> gastrade, bool isGastrade, bool isFindUtxo, const std::string &encodedInfo, txAck *ack);

/**
 * @brief
 *
 * @param       fromAddr:
 * @param       lockAmount:
 * @param       lockType:
 * @param       gastrade:
 * @param       isGastrade:
 * @param       isFindUtxo:
 * @param       encodedInfo:
 * @param       ack:
 */
void ReplaceCreateLockTransaction(const std::string & fromAddr, uint64_t lockAmount, int32_t lockType, const std::pair<std::string,std::string>& gastrade,
                                                   bool isGastrade, bool isFindUtxo, const std::string& encodedInfo, txAck* ack);
/**
 * @brief       
 * 
 * @param       fromAddr: 
 * @param       utxoHash: 
 * @param       gastrade: 
 * @param       isGastrade: 
 * @param       isFindUtxo: 
 * @param       encodedInfo: 
 * @param       ack: 
 */
void ReplaceCreateUnLockTransaction(const std::string& fromAddr, const std::string& utxoHash,const std::pair<std::string,std::string>& gastrade,
                                                    bool isGastrade, bool isFindUtxo, const std::string& encodedInfo, txAck* ack);
/**
 * @brief       
 * 
 * @param       fromAddr: 
 * @param       gastrade: 
 * @param       beinTime: 
 * @param       endTime: 
 * @param       assetName: 
 * @param       rate: 
 * @param       contractAddr: 
 * @param       isFindUtxo: 
 * @param       encodedInfo: 
 * @param       ack: 
 */
void ReplaceCreateProposalTransaction(const std::string& fromAddr, const std::pair<std::string,std::string>& gastrade, std::string& identifier, std::string& title,
                                                    uint64_t beinTime, uint64_t endTime, std::string assetName, std::string rate, std::string contractAddr, uint64_t minVote, bool isFindUtxo, const std::string& encodedInfo, txAck* ack);
/**
 * @brief       
 * 
 * @param       fromAddr: 
 * @param       gastrade: 
 * @param       beinTime: 
 * @param       endTime: 
 * @param       proposalHash: 
 * @param       isFindUtxo: 
 * @param       encodedInfo: 
 * @param       ack: 
 */
void ReplaceCreateRevokeProposalTransaction(const std::string& fromAddr, const std::pair<std::string,std::string>& gastrade,
                                                    uint64_t beinTime, uint64_t endTime, std::string proposalHash, uint64_t minVote, bool isFindUtxo, const std::string& encodedInfo, txAck* ack);
/**
 * @brief       
 * 
 * @param       fromAddr: 
 * @param       gastrade: 
 * @param       voteHash: 
 * @param       pollType: 
 * @param       voteTxType: 
 * @param       isFindUtxo: 
 * @param       encodedInfo: 
 * @param       ack: 
 */
void ReplaceCreateVoteTransaction(const std::string& fromAddr, const std::pair<std::string,std::string>& gastrade,
                                                    const std::string& voteHash, const int pollType, const global::ca::TxType& voteTxType, bool isFindUtxo, const std::string& encodedInfo, txAck* ack);

/**
    * @brief       
    * 
    * @param       Addr: 
    * @param       encodedInfo: 
    * @param       ack: 
    * @return      
    */

void ReplaceCreateTreasuryTransaction(const std::string& addr, const std::string& encodedInfo,txAck* ack);

/**
    * @brief       
    * 
    * @param       outTx: 
    * @param       height: 
    * @param       info: 
    * @param       type: 
    * @return      int 
    */
int SendMessage(CTransaction & outTx,int height,Vrf &info,TxHelper::vrfAgentType type);



#endif

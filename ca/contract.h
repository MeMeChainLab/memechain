#ifndef __CA_CONTRACT_H__
#define __CA_CONTRACT_H__

#include <string>
#include <unordered_map>

#include <evmc/evmc.hpp>
#include <ca/evm/evm_host.h>
#include <transaction.pb.h>
#include "ca/evm/evm_environment.h"
#include "txhelper.h"
#include "global.h"

namespace Evmone
{
    /**
     * @brief       
     * 
     * @param       host: 
     * @param       txHash:
     * @param       TxType:
     * @param       transactionVersion:
     * @param       jTxInfo: 
     * @param       contractPreHashCache:   
     * @return      int 
     */
    int
    ContractInfoAdd(const EvmHost &host, const std::string &txHash, global::ca::TxType TxType,
                    uint32_t transactionVersion,
                    nlohmann::json &jTxInfo, std::map<std::string, std::string> &contractPreHashCache, bool isCheckContractPreHash = false);
    /**
     * @brief       
     * 
     * @param       fromAddr: 
     * @param       toAddr: 
     * @param       transferrings: 
     * @param       jTxInfo: 
     * @param       height: 
     * @param       gasCost: 
     * @param       outTx: 
     * @param       type: 
     * @param       info_: 
     * @param       contractTip: 
     * @return      int 
     */
    int FillCallOutTx(const std::string &fromAddr, const std::string &toAddr, const std::vector<TransferInfo> &transferrings,
                      const std::pair<std::string, std::string> &gasTrade,
                      const nlohmann::json &jTxInfo, int64_t gasCost, CTransaction &outTx, TxHelper::vrfAgentType &type,
                      const std::string &encodedInfo, bool isFindUtxo);

    /**
     * @brief       
     * 
     * @param       fromAddr: 
     * @param       toAddr: 
     * @param       txType:
     * @param       transferrings: 
     * @param       gasCost: 
     * @param       outTx: 
     * @param       contractTip: 
     * @param       utxoHashs: 
     * @param       isGenSign: 
     * @return      int 
     */
    int GenCallOutTx(const std::string &fromAddr, const std::string &toAddr, global::ca::TxType txType, const std::vector<TransferInfo> &transferrings, const std::pair<std::string, std::string> &gasTrade,
                     int64_t gasCost, CTransaction &outTx, std::vector<std::string> &utxoHashs, bool isFindUtxo,bool isGenSign = true, bool isInflowTx = false,bool isOutflowTx = false);
    /**
     * @brief       
     * 
     * @param       tx: 
     * @param       callOutTx: 
     * @return      int 
     */
    int VerifyUtxo(const std::string& sender, const CTransaction& tx, const CTransaction& callOutTx, int mapping);

    /**
     * @brief       
     * 
     * @param       fromAddr: 
     * @param       toAddr: 
     * @param       transferrings: 
     * @param       jTxInfo: 
     * @param       gasCost: 
     * @param       height: 
     * @param       outTx: 
     * @param       type: 
     * @param       info_: 
     * @return      int 
     */
    int FillDeployOutTx(const std::string &fromAddr, const std::string &toAddr, const std::vector<TransferInfo> &transferrings,
                        const std::pair<std::string, std::string> &gasTrade,
                        const nlohmann::json &jTxInfo, int64_t gasCost, CTransaction &outTx, TxHelper::vrfAgentType &type,
                        const std::string &encodedInfo, bool isFindUtxo);

    /**
     * @brief       
     * 
     * @param       from:
     * @param       host:
     * @return      int
     */
    int DeployContract(const std::string &from, EvmHost &host, evmc_message &message, const std::string &to,
                       int64_t blockTimestamp, int64_t blockPrevRandao, int64_t blockNumber, const std::string &gasType);

    /**
     * @brief       
     * 
     * @param       from:
     * @param       strInput:
     * @param       host:
     * @param       contractTransfer: 
     * @return      int 
     */
    int
    CallContract(const std::string &from, const std::string &strInput, EvmHost &host, const uint64_t &contractTransfer,
                 const std::string &to, evmc_message &message, int64_t blockTimestamp, int64_t blockPrevRandao,
                 int64_t blockNumber, const std::string &gasType);

    int RPC_CallContract(const std::string &from, const std::string &strInput, EvmHost &host, const uint64_t &contractTransfer,
                 const std::string &to, evmc_message &message, int64_t blockTimestamp, int64_t blockPrevRandao,
                 int64_t blockNumber,const std::string &gasType);
    

    /**
     * @brief       Get the Storage object
     * 
     * @param       host: 
     * @param       jStorage: 
     * @param       dirtyContract: 
     */
    void GetStorage(const EvmHost &host, nlohmann::json &jStorage, std::set<evmc::address> &dirtyContract);
    /**
     * @brief       
     * 
     * @param       host: 
     * @param       calledContract: 
     */
    void GetCalledContract(const EvmHost& host, std::vector<std::string>& calledContract);
    void
    FillStorageMap(const std::pair<std::string, std::string> &item, std::map<std::string, std::string> &storages,
                   const std::string &contractAddr);
    int HandleMappingFunction(const std::pair<std::string, std::string> &gasTrade, const std::string &hexStr, const std::string &contractAddr, const std::string &OwnerEvmAddr, 
                                    CTransaction &outTx, nlohmann::json &jTxInfo, bool isFindUtxo, bool &isMappingTx );
    
    int ValidateMappingTransaction(const std::string &hexStr, const std::string &contractAddr, const std::string &OwnerEvmAddr, const CTransaction &outTx);
    
    int FillOutflowVin(const std::pair<std::string, std::string> &gasTrade, CTxUtxos *txUtxo, uint64_t &total, bool isFindUtxo);
}


//namespace Wasmtime
//{
//    /**
//     * @brief
//     *
//     * @param       fromAddr:
//     * @param       code_str:
//     * @param       strOutput:
//     * @param       gasCost:
//     * @return      int
//     */
//    int DeployWasmContract(const std::string &fromAddr, const std::string &code_str, std::string &strOutput ,int64_t &gasCost);
//    /**
//     * @brief
//     *
//     * @param       fromAddr:
//     * @param       strDeployer:
//     * @param       strDeployHash:
//     * @param       strInput:
//     * @param       contractFunName:
//     * @param       strOutput:
//     * @param       gasCost:
//     * @return      int
//     */
//    int CallWasmContract(const std::string &fromAddr, const std::string &strDeployer, const std::string &strDeployHash,
//                        const std::string &strInput, const std::string &contractFunName, std::string &strOutput, int64_t &gasCost);
//    /**
//     * @brief
//     *
//     * @param       fromAddr:
//     * @param       toAddr:
//     * @param       txType:
//     * @param       gasCost:
//     * @param       outTx:
//     * @param       contractTip:
//     * @param       utxoHashs:
//     * @param       isGenSign
//     * @return      int
//     */
//    int GenCallWasmOutTx(const std::string &fromAddr, const std::string &toAddr, global::ca::TxType txType, int64_t gasCost, CTransaction& outTx,
//            const uint64_t& contractTip, std::vector<std::string>& utxoHashs, bool isGenSign = true);
//
//    /**
//     * @brief
//     *
//     * @param       fromAddr:
//     * @param       toAddr:
//     * @param       txType:
//     * @param       jTxInfo:
//     * @param       height:
//     * @param       outTx:
//     * @param       type:
//     * @param       info_:
//     * @param       contractTip:
//     * @return      int
//     */
//    int FillWasmOutTx(const std::string &fromAddr, const std::string &toAddr, global::ca::TxType txType,const nlohmann::json &jTxInfo,
//            uint64_t height, int64_t gasCost, CTransaction &outTx, TxHelper::vrfAgentType &type, Vrf &info_, const uint64_t& contractTip);
//    /**
//     * @brief
//     *
//     * @param       txHash:
//     * @param       jTxInfo:
//     * @param       txType:
//     * @param       transactionVersion:
//     * @param       contractPreHashCache:
//     * @return      int
//     */
//    int ContractInfoAdd(const std::string &txHash, nlohmann::json& jTxInfo, global::ca::TxType txType, uint32_t transactionVersion, std::map<std::string, std::string> &contractPreHashCache);
//    /**
//     * @brief
//     *
//     * @param       calledContract:
//     */
//    void GetCalledContract(std::vector<std::string>& calledContract);
//
//}

namespace ContractCommonInterface
{
    /**
     * @brief       
     * 
     * @param       fromAddr: 
     * @param       expend: 
     * @param       tempGas: 
     * @param       txUtxo: 
     * @param       utxoHashs: 
     * @param       total: 
     * @param       isFindUtxo: 
     * @param       isSign:
     * @param       isSign:
     * @return      int 
     */
    int GenVin(const std::pair<std::string, std::string>& addressCurrencyMapping, const uint64_t& expend, const uint64_t& tempGas, CTxUtxos * txUtxo, 
            std::vector<std::string>& utxoHashs, uint64_t& total, bool isFindUtxo, bool isSign,const std::string& sender = "");
    /**
     * @brief       
     * 
     * @param       fromAddr: 
     * @param       toAddr: 
     * @param       txType: 
     * @param       transfersMap: 
     * @param       gasCost: 
     * @param       outTx: 
     * @param       contractTip: 
     * @param       utxoHashs: 
     * @param       isGenSign: 
     * @return      int 
     */
    int fillingTransactions(const std::string &fromAddr, const std::string &toAddr, global::ca::TxType txType,
                            const std::map<std::string, std::map<std::string, uint64_t>> &transfersMap, const std::pair<std::string, std::string> &gasTrade, const int64_t gasCost,
                            CTransaction &outTx, std::vector<std::string> &utxoHashs, bool isFindUtxo, bool isGenSign = true, bool isInflowTx = false, bool isOutflowTx = false);
    /**
     * @brief       
     * 
     * @param       fromAddr: 
     * @param       txType: 
     * @param       height: 
     * @param       outTx: 
     * @param       type: 
     * @param       info_: 
     * @return      int 
     */
    int fillingTransactions(const std::string &fromAddr, global::ca::TxType txType, 
                            CTransaction &outTx, TxHelper::vrfAgentType &type);
    /**
     * @brief       
     * 
     * @param       strDeployer: 
     * @param       strDeployHash: 
     * @param       contractAddress: 
     * @param       deployTx: 
     * @return      int 
     */
    int GetDeployTxByDeployData(const std::string & strDeployer, const std::string & strDeployHash, std::string & contractAddress, CTransaction & deployTx);

}


/**
 * @brief       
 * 
 * @param       msg: 
 * @param       host:
 * @return      int
 */
int ExecuteByEvmone(const evmc_message &msg, EvmHost &host);

/**
 * @brief       
 * 
 */
void TestAddressMapping();
#endif

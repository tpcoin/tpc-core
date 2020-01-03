// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2019 The TPC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("00000a9c37d05e9e758a8f635dcd2807d0927b3b778de36f2fd9b47ffbc5e347"))
	;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1577044800, // * UNIX timestamp of last checkpoint block
    0,    	// * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    3000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("00000a9c37d05e9e758a8f635dcd2807d0927b3b778de36f2fd9b47ffbc5e347"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1577044800,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("00000a9c37d05e9e758a8f635dcd2807d0927b3b778de36f2fd9b47ffbc5e347"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1577044800,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x01;
        pchMessageStart[1] = 0xaa;
        pchMessageStart[2] = 0xba;
        pchMessageStart[3] = 0xab;
        vAlertPubKey = ParseHex("04935571b8bb3780c9c995146380713fcc487636240b09d9198059fcea177c920bc5b16e0247b5aa75703febdf0959ad6d8d6bbc621640ffb40b4c79a373974b20");
        nDefaultPort = 16521;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // TPC starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 4000000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60;
        nTargetSpacing = 2 * 60;
        nMaturity = 60;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1;
        nZerocoinStartHeight = 101;
        nAccumulatorStartHeight = 50;
        nZerocoinStartTime = 1529726034;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint

        const char* pszTimestamp = "December 22 2019 - TPC CRYO Launch";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1577044800; // UTC Sunday 22 December 2019 20:00:00
        genesis.nBits = 0x1E0FFFF0;
        genesis.nNonce = 1368171;

		hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("00000a9c37d05e9e758a8f635dcd2807d0927b3b778de36f2fd9b47ffbc5e347"));
        assert(genesis.hashMerkleRoot == uint256("36425cffbad7d3117dac63e254e9cb5cc2a6342e48c414e694f1f5bcf154a776"));

		vSeeds.push_back(CDNSSeedData("167.86.104.232", "167.86.104.232"));
		vSeeds.push_back(CDNSSeedData("164.68.110.103", "164.68.110.103"));
		vSeeds.push_back(CDNSSeedData("164.68.111.75", "164.68.111.75"));
		vSeeds.push_back(CDNSSeedData("116.203.156.64", "116.203.156.64"));
		vSeeds.push_back(CDNSSeedData("159.69.190.7", "159.69.190.7"));
		vSeeds.push_back(CDNSSeedData("95.216.164.118", "95.216.164.118"));
		vSeeds.push_back(CDNSSeedData("116.202.26.146", "116.202.26.146"));
		vSeeds.push_back(CDNSSeedData("164.68.106.143", "164.68.106.143"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 23);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 223);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x02)(0x2A)(0x3A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x00)(0x20)(0x22)(0x02).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x1e)(0xf1).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04eef854f7585aff3ca75f67e587a272649b27bcc2ddfc84f74f53321959a98de104bb6fe1cf06035078aca811a82da7b8a2386883f715965abd7f121791b49e5a";
        strObfuscationPoolDummyAddress = "TSvAutvPPoJSXkkhFbM81NJwrH5WWwN859";
        nStartMasternodePayments = 1516371317;

        /** Zerocoin */
        zerocoinModulus = "31629371982883654747876637397977794903229047353658840926060123331980132797095193443400483581955155"
            "9140326217928527729421120143947632766307118699382872851428016259864502927433364349120863346768110353968977154492"
            "4529916275361138080563068024877581070714668896757923763202421476956797848068247425087970545553584192099508855393"
            "2517732108666167108010176497978305278075734300480511464917311796709554446862604905505722840193080357517097751624"
            "5962345574625638911099444052688081364332608166414911619220798571364171342788070783015395049932464398621838539210"
            "24875541895683682393230943067733828588974967606248865806878122888210000";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * ZCENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee

        nStakeMinConfirmations = 720;   // Required number of confirmations
        nStakeMinAmount = 50 * COIN;    // Minimum required staking amount
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xfb;
        pchMessageStart[2] = 0xfc;
        pchMessageStart[3] = 0xfd;
        vAlertPubKey = ParseHex("04935571b8bb3780c9c995146380713fcc487636240b09d9198059fcea177c920bc5b16e0247b5aa75703febdf0959ad6d8d6bbc621640ffb40b4c79a373974b20");
        nDefaultPort = 11313;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; 
        nTargetSpacing = 2 * 60;  
        nLastPOWBlock = 200;
        nBTChangeBlock = 1000;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; 
        nMaxMoneyOut = 21000000 * COIN;
        nZerocoinStartHeight = 50;
        nZerocoinStartTime = 1529726039;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint
        genesis.nTime = 1577044800;
        genesis.nNonce = 1368171;

	    hashGenesisBlock = genesis.GetHash();
		assert(hashGenesisBlock == uint256("00000a9c37d05e9e758a8f635dcd2807d0927b3b778de36f2fd9b47ffbc5e347"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet.tpc.io", "testnet.tpc.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 110);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 115);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 214);
        // Testnet tpc BIP32 pubkeys
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x2a)(0x12)(0x11).convert_to_container<std::vector<unsigned char> >();
        // Testnet tpc BIP32 prvkeys
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x41)(0x11)(0x1a).convert_to_container<std::vector<unsigned char> >();
        // Testnet tpc BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "041f844152b871ebd012d40cc5777218da54fab5e89c2236ff0e88e6f6783d474dc6779b47cba883495bcc7ce99b273503031fffca5bca026a509ab635e3959738";
        strObfuscationPoolDummyAddress = "TSvAutvPPoJSXkkhFbM81NJwrH5WWwN859";
        nStartMasternodePayments = 1420837558;
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nStakeMinConfirmations = 30;    // Required number of confirmations
        nStakeMinAmount = 1000 * COIN;  // Minimum required staking amount
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xf3;
        pchMessageStart[3] = 0xf4;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60;
        nTargetSpacing = 2 * 60;        
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1577044800;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1368171;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 36210;
        assert(hashGenesisBlock == uint256("00000a9c37d05e9e758a8f635dcd2807d0927b3b778de36f2fd9b47ffbc5e347"));

        vFixedSeeds.clear(); 
        vSeeds.clear();      

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

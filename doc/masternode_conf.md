Multi masternode config
=======================

The multi masternode config allows you to control multiple masternodes from a single wallet. The wallet needs to have a valid collateral output of 1000 coins for each masternode. To use this, place a file named masternode.conf in the data directory of your install:
 * Windows: %APPDATA%\TPC\
 * Mac OS: ~/Library/Application Support/TPC/
 * Unix/Linux: ~/.tpc/

The new masternode.conf format consists of a space seperated text file. Each line consisting of an alias, IP address followed by port, masternode private key, collateral output transaction id, collateral output index, donation address and donation percentage (the latter two are optional and should be in format "address:percentage").

Example:
```
mn1 127.0.0.2:16521 8WKr9qZ5s87osUoKrM4F5or4akvcwThKsLd2LpdsynYUAuKYMfU cca4893518c2490cec64e250044d2f85d0634bdb09b30d4bf2879f78c0c55af6 0
mn2 127.0.0.3:16521 8W8wTbNzgt1aYrDMLMrBQxMPMZLgGxmbUCoCr2vj9RnoSD3ZcaB 52c5fad06638629d6c8ed0b674a2870e2723d1f4106e432a928d49544d383116 0 TDEVVVUzKLebFXrPiNepWkV4MGeU4xPhgR:33
mn3 127.0.0.4:16521 8VCHbakAN9RC2mSm3NeBT7KdxtsbTDz38SLLARWwfzzP6VCLyvU d7ba891d4da028ce72f1391f7b3e850761c194f870a206b4765c9064eb6a45d1 1 TDEVVVUzKLebFXrPiNepWkV4MGeU4xPhgR
```

In the example above:
* the collateral for mn1 consists of transaction e605b63dbadc354e93dd9590c3530e841c9a57d253fdb4a37ddf97b22cff572c, output index 0 has amount 1000
* masternode 2 will donate 33% of its income
* masternode 3 will donate 100% of its income


The following new RPC commands are supported:
* list-conf: shows the parsed masternode.conf
* start-alias \<alias\>
* stop-alias \<alias\>
* start-many
* stop-many
* outputs: list available collateral output transaction ids and corresponding collateral output indexes

When using the multi masternode setup, it is advised to run the wallet with 'masternode=0' as it is not needed anymore.

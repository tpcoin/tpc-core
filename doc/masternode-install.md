# TPC
Shell script to install a [TPC Masternode](https://tpc.io/) on a Linux server running Ubuntu 16.04. Use it on your own risk.
***

## Installation
```
wget -q https://raw.githubusercontent.com/harcomia/Harcomia-core/master/tpc_install.sh

bash tpc_install.sh
```
***

## Desktop Wallet Setup 

After the MN is up and running, you need to configure the desktop wallet accordingly. Here are the steps:  
1. Open the TPC(TPC) Desktop Wallet.  
2. Go to RECEIVE and create a New Address: **MN1**  
3. Send **1000** TPC to **MN1**. You need to send all 1000 coins in one single transaction.
4. Wait for 15 confirmations.  
5. Go to **Help -> "Debug Window - Console"**  
6. Type the following command: **masternode outputs**  
7. Go to  **Tools -> "Open Masternode Configuration File"**
8. Add the following entry:
```
Alias Address Privkey TxHash TxIndex
```
* Alias: **MN1**
* Address: **VPS_IP:PORT**
* Privkey: **Masternode Private Key**
* TxHash: **First value from Step 6**
* TxIndex:  **Second value from Step 6**
9. Save and close the file.
10. Go to **Masternode Tab**. If you tab is not shown, please enable it from: **Settings - Options - Wallet - Show Masternodes Tab**
11. Click **Update status** to see your node. If it is not shown, close the wallet and start it again. Make sure the wallet is un
12. Select your MN and click **Start Alias** to start it.
13. Alternatively, open **Debug Console** and type:
```
startmasternode "alias" "0" "my_mn"
``` 
14. Login to your VPS and check your masternode status by running the following command:
```
tpc-cli masternode status
```
***

## Usage:
```
tpc-cli masternode status  
tpc-cli getinfo
```
Also, if you want to check/start/stop **TPC**, run one of the following commands as **root**:
```
systemctl status TPC #To check if TPC service is running  
systemctl start TPC #To start TPC service  
systemctl stop TPC #To stop TPC service  
systemctl is-enabled TPC #To check if TPC service is enabled on boot  
```  
***
Credit to @Zoldur for writing the original install script.

https://github.com/zoldur

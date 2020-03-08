CHBToken 5.0.0.0 & CHBTPaygate
===========================

*  CHBToken is a PoS-based cryptocurrency.
*  CHBToken is a secure document upload system with document storage and high security encryption.
*  CHBToken with CHBTPaygate provides an option to cryptographically sign and store encrypted documents on the CHBToken Blockchain utilizing a 1MB encryption key and verification hash.
*  CHBToken offers an option for companies to run CHBTPaygate internally while still allowing the public CHBToken to remain decentrally linked.
*  CHBToken allows file upload of up to 1000MB per file.
 
This Github contains only the source code for CHBToken. It does not contain the source code for CHBTPaygate.
For CHBTPaygate please refer to the section below specifically for companies.

CHBToken Overview
===========================
*  **Initial Amount:** 2.5 Million CHBToken only
*  **Increase:** 0.06 CHBToken per successful stake
*  **Block time:** 60 seconds
*  **Type:** PoS Coin
*  **Maturity:** 501 blocks
*  **Transfer Maturity:** 10 Blocks
*  **Transfer Speed:** Virtually instant (individual times vary slightly)
*  **Protocol:** 60018
*  **First Block on:** 2017-10-16 17:36:01
*  **Name:** CHBT

CHBToken 5.0.0.0 Source Code and Windows Wallet
===========================
**The Source Code (this repository):** https://github.com/CHBToken/chbtokenV5.x

**The Windows Wallet CHBTLauncher is available for download on:** https://github.com/CHBToken/CHBTokenV5_Wallet

**Official Website:** https://chbt.ch

Can I mine CHBToken?
============================
No, CHBToken cannot be mined. You can only stake CHBToken.

Can I run a Master Node?
============================
No, the CHBToken protocol does not support Master-Nodes.

WARNING FROM THE DEVELOPERS!!
===========================
To ensure you have a great user experience we would like to provide you with some hints we recommend.

However, you as user are ultimately responsible for keeping your CHBToken Wallet secure and backed up.

`IF YOU LOSE YOUR WALLET.DAT FILE ALL YOUR CHBTOKEN COINS ARE LOST`

`IF YOU LOSE YOUR PRIVATE KEY YOU WILL NOT BE ABLE TO ACCESS YOUR ENCRYPTED DOCUMENTS`

`ALLWAYS BACKUP YOUR WALLET.DAT FILE, YOUR WALLET.DAT FILE IS LOCATED IN c:\USERS\YOURUSERNAME\APPDATA\ROAMING\CHBTOKEN`

`NEVER SHARE YOUR WALLET PASSWORD WITH ANYONE. THE CHBTOKEN DEVELOPERS WILL NEVER ASK FOR A PASSWORD`

`NEVER DOWNLOAD CHBTOKEN WALLET FROM ANOTHER SOURCE EXCEPT THE OFFICIAL SOURCE OF CHBTOKEN`

`ALWAYS PROTECT YOUR CHBTOKEN WALLET WITH A SECURE PASSWORD`

`ALLWAYS KEEP THE PASSWORD SAFE. THE CHBTOKEN DEVELOPERS CANNOT RECOVER YOUR PASSWORD`

`MAKE REGULAR BACKUPS OF YOUR WALLET.DAT FILE`

`IF YOU ADD A NEW RECEIVING ADDRESS MAKE A NEW BACKUP OF YOUR WALLET.DAT FILE`

My CHBToken Wallet is not connecting
==============================
If you started off with a clean install and your CHBToken Wallet is not connecting you can do the following:

1.) Go to Chainz and view the latest [Node List](https://chainz.cryptoid.info/chbt/#!network)

This Node list displays all active nodes for the last 24hr period.

A.) Open the CHBtoken wallet and go to: Help/Debug Windows/Console

B.) Within the entry field type in: **addnode (the IP address found on the Node List) add**, e.g. (example) addnode xxx.xxx.xxx.xxx add

C.) Press enter.

Repeat stepp B and C for 3 different IP addresses. This will then kick-start your connections and your wallet should begin to sync with the CHBToken Blockchain.

Should the Wallet still not connect after the above you should ensure the CHBToken Wallet is not blocked by any firewalls on your PC as this will prevent the Wallet from connecting to the network.

Bug fixes in CHBToken 5.0.0.0
===========================
**Bug Fixes**
Version 5.0.0.0 contains various bug fixes on text, images and functionalities.

New functions in CHBToken 5.0.0.0
===========================
For latest information and new features please check https://chbt.ch, however in a nutshell the following features are new to V5.0.0.0
1. File Signing 
2. File Signing & Upload
3. File Encryption on uploaded files
4. File Sharing on uploaded files
5. In-Wallet file explorer on signed files
6. Certificate on signed files
7. Verification explorer for signed files
8. CHBT Trust Authority
9. In Wallet direct purchase over credit card
10. New CHBTPaygate chain for online file storage for up to 1000MB per file
11. Autoupdate feature
12. New local file structure for signed files within appdata
13. Option to open / browse signed files from the wallet
13. Additional readme section within the wallet
14. Additional high encryption of 1MB key for uploaded files
15. Additional password & encryption for file sharing on files

**Document Upload**

CHBToken as of version 5.0.0.0 allows users to upload documents directly from the wallet in an encrypted format to be shared with others.

1.  Uploaded documents are encrypted
2.  Each document receives its own unique hash and signature as proof
3.  Documents can be shared with others using the hash and link.
4.  Documents are encrypted with your own private encryption key

**Fees for document upload within CHBToken Wallet**

To ensure each user knows the upfront cost of a document upload / signing a fixed fee has been indroduced.

1.  The fees to sign and upload are set at a fixed rate of 5 EUR per 10MB document per year (after the initial 10MB file size).
2.  Users can choose between 1 and 10 years storage for documents within CHBToken.
3.  Fees are deducted directly as CHBToken from within the User's Wallet.

`After the selected time period ends documents are automatically removed unless the user chooses to renew the document for a new storage period`

**Calculation of Fees**

Document sizes and fees

| Document Size | Sign Only | Upload & Signing Fee| Cost in CHBToken |
| ------ | ------ | ------ | ------ |
| < 10 MB | 5 EUR | 10 EUR | Day rate |
| > 10 MB | 5 EUR | 15 EUR | Day rate |
| > 20 MB | 5 EUR | 20 EUR | Day rate |
| > 30 MB | 5 EUR | 25 EUR | Day rate |
| > 40 MB | 5 EUR | 30 EUR | Day rate |

Document sizes are limited to a maximum of 1000MB per document

**Example of cost of a 10 MB document upload within CHBToken Wallet**

We assume for this example following:
- CHBToken price on an exchange is 2.00 USD per CHBToken
- CHBTPaygate fee is 5 USD per 10MB
- Size of Document < 10MB


| Document Size | Price of CHBToken | Cost of Document Upload | Cost in CHBToken | Standard TRX Fee of CHBToken |
| ------ | ------ | ------ | ------ | ------ |
| < 10 MB | 2.00 EUR | 5 EUR | 2.5 CHBToken |  0.0001 CHBToken |

So, to upload a document with a size < 10MB the cost is 2.5001 CHBToken which is directly deducted from the user's wallet. 

The fiat cost is a function of the current CHBToken price and the transaction fee e.g.

5.00 EUR (for document  < 10mb ) + Transaction fee of CHBToken (0.0001)

The EUR fee for the document upload is converted to the CHBToken price. 

This way user always knows that the cost in fiat is 5.00 EUR regardless of the current CHBToken price.


**CHBToken has a secondary chain (CHBTPaygate) included**

The secondary chain (CHBTPaygate) has been developed by the CHBToken Developers and is running as a separate chain to the CHBToken chain to avoid bloat within CHBToken.

* CHBToken remains a PoS coin with decentralised approach.
* The secondary CHBTPaygate chain has no size limit but is set to a maximum of 1000MB per Document upload.
* Each user has their own private encryption key and public keys are stored on the public key server.

NOTE: If a private key is lost then there is no way to recover this key

Is there an Explorer for CHBToken?
===========================
Yes, you can view the information for CHBToken on Chainz.cryptoid.info: [Go to CHBToken Explorer](https://chainz.cryptoid.info/chbt/ )

How to get CHBToken?
===========================
You can obtain CHBToken via the following options:
* [Y]  By purchasing from a cryptocurrency exchange on which offers CHBToken
* [Y]  By receiving CHBToken from another person directly into your CHBToken Wallet
* [Y]  By Staking CHBToken within your Wallet. A sucessfull stake provides a reward of 0.06 CHBToken
* [Y]  By purchasing CHBTokens at a fixed rate directly from within the walled using your credit card.
When purchasing CHBTPaygate tokens you will receive an EUR invoice.

What is the Transaction Fee?
===========================
CHBToken carries a minimum transaction fee of 0.0001 CHBToken for each transaction (e.g. transfer CHBTokens in or out of your wallet or to submit a request for signing).

This transaction fee goes back to CHBToken to support the CHBToken Chain.

Where does the cost for CHBTPaygate insertion go?
===========================
The fees for CHBTPaygate document insertion are used for:
*  Supporting server hosting costs
*  Maintaining server infrastructure
*  Supporting future development
*  Supporting running cost for the CHBToken Company
*  Provide an income to the CHBToken developers
 
The fees for CHBTPaygate are not burned and are used as described above.

Companies
===========================

If your company would like to operate your own internal version of CHBTPaygate for your document storage needs, we can provide the following options:

We would provide you with access to the CHBTPaygate source code along with the following information:
*  Access to the Github Repository of CHBTPaygate
*  Install and setup instructions
*  API documentation
*  Access to the 1MB encryption functionality
*  4 hrs online support (via phone or other medium such as skype) to set up CHBTPaygate within your company
 
The cost for an internal CHBTPaygate License and right to use it without limitation within your company can be requested by using the contact form on https://chbt.ch.

An internal usage licence however does not grant you the right to repackage, resell or otherwise redistribute CHBTPaygate as your own.
You can however fully customise it to fit your internal needs. This means that you can also customize CHBToken to link into your internal CHBTPaygate solution.

Development Process
===========================

Developers work in their own trees, then submit pull requests when they believe their feature or bug fix is ready.

The patch will be accepted if there is broad consensus that it is a
beneficial. Developers should expect to rework and resubmit patches
if they don't match the project's coding conventions (see coding.txt)
or are controversial.

The master branch is regularly built and tested, but is not guaranteed
to be completely stable. Tags are regularly created to indicate new
stable release versions of CHBToken.

Feature branches are created when there are major new features being
worked on by several people.

From time to time a pull request will become outdated. If this occurs, and
the pull is no longer automatically mergeable; a comment on the pull will
be used to issue a warning of closure. The pull will be closed 15 days
after the warning if action is not taken by the author. Pull requests closed
in this manner will have their corresponding issue labeled 'stagnant'.

Issues with no commits will be given a similar warning, and closed after
15 days from their last activity. Issues closed in this manner will be 
labeled 'stale'.

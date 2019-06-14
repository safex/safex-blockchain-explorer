# Safex Blockchain Explorer

This is the Safex blockchain explorer. This is a fork of [Onion Monero Blockchain Explorer](https://github.com/moneroexamples/onion-monero-blockchain-explorer)



## Safex Blockchain Explorer features

The key features of the Safex Blockchain Explorer are:

 - no cookies, no web analytics trackers, no images,
 - by default no JavaScript, but can be enabled for client side decoding and proving transactions,
 - open sourced,
 - made fully in C++,
 - showing encrypted payments ID,
 - showing ring signatures,
 - showing transaction extra field,
 - showing public components of Safex addresses,
 - decoding which outputs and mixins belong to the given Safex address and viewkey,
 - can prove that you send Safex cash to someone,
 - detailed information about ring members, such as, their age, timescale and their ring sizes,
 - showing number of amount output indices,
 - support Safex testnet and stagenet networks,
 - tx checker and pusher for online pushing of transactions,
 - estimate possible spendings based on address and viewkey,
 - can provide total amount of all miner fees,
 - decoding encrypted payment id,
 - decoding outputs and proving txs sent to sub-address.



## Compilation on Ubuntu 18.04

##### Compile latest Safex development version

Download and compile recent safexcore into your home folder:

```bash
# first install safex dependecines
sudo apt update

sudo apt install git build-essential cmake libboost-all-dev miniupnpc libunbound-dev graphviz doxygen libunwind8-dev pkg-config libssl-dev libcurl4-openssl-dev libgtest-dev libreadline-dev libzmq3-dev libsodium-dev libpcsclite-dev

# go to home folder
cd ~

git clone --recursive https://github.com/safex/safexcore

cd safeccore/

# checkout last monero version
git checkout master

make
```

##### Compile and run the explorer

Once the Safex is compiles, the explorer can be downloaded and compiled
as follows:

```bash
cd ~

# download the source code
git clone https://github.com/safex/safex-blockchain-explorer.git

# enter the downloaded sourced code folder
cd safex-blockchain-explorer

# make a build folder and enter it
mkdir build && cd build

# create the makefile
cmake ..

# altearnatively can use: cmake -DSAFEX_DIR=/path/to/safexcore_folder ..
#
# also can build with ASAN (sanitizers), for example
# cmake -DSANITIZE_ADDRESS=On ..

# compile
make
```


To run it:
```
./safex-explorer
```

By default it will look for blockchain in its default location i.e., `~/.safex/lmdb`.
You can use `-b` option if its in different location.

For example:

```bash
./safex-explorer -b /home/user/non-defult-safex-location/lmdb/
```

Example output:

```bash
$ ./xmrblocks
2016-May-28 10:04:49.160280 Blockchain initialized. last block: 1056761, d0.h0.m12.s47 time ago, current difficulty: 1517857750
(2016-05-28 02:04:49) [INFO    ] Crow/0.1 server is running, local port 8081
```

Go to your browser: http://127.0.0.1:8081

## The explorer's command line options

```
xmrblocks, Safex Blockchain Explorer:
  -h [ --help ] [=arg(=1)] (=0)         produce help message
  -t [ --testnet ] [=arg(=1)] (=0)      use testnet blockchain
  -s [ --stagenet ] [=arg(=1)] (=0)     use stagenet blockchain
  --enable-pusher [=arg(=1)] (=0)       enable signed transaction pusher
  --enable-mixin-details [=arg(=1)] (=0)
                                        enable mixin details for key images,
                                        e.g., timescale, mixin of mixins, in tx
                                        context
  --enable-key-image-checker [=arg(=1)] (=0)
                                        enable key images file checker
  --enable-output-key-checker [=arg(=1)] (=0)
                                        enable outputs key file checker
  --enable-json-api [=arg(=1)] (=1)     enable JSON REST api
  --enable-tx-cache [=arg(=1)] (=0)     enable caching of transaction details
  --show-cache-times [=arg(=1)] (=0)    show times of getting data from cache
                                        vs no cache
  --enable-block-cache [=arg(=1)] (=0)  enable caching of block details
  --enable-js [=arg(=1)] (=0)           enable checking outputs and proving txs
                                        using JavaScript on client side
  --enable-autorefresh-option [=arg(=1)] (=0)
                                        enable users to have the index page on
                                        autorefresh
  --enable-emission-monitor [=arg(=1)] (=0)
                                        enable Safex total emission monitoring
                                        thread
  -p [ --port ] arg (=8081)             default explorer port
  --testnet-url arg                     you can specify testnet url, if you run
                                        it on mainnet or stagenet. link will
                                        show on front page to testnet explorer
  --stagenet-url arg                    you can specify stagenet url, if you
                                        run it on mainnet or testnet. link will
                                        show on front page to stagenet explorer
  --mainnet-url arg                     you can specify mainnet url, if you run
                                        it on testnet or stagenet. link will
                                        show on front page to mainnet explorer
  --no-blocks-on-index arg (=10)        number of last blocks to be shown on
                                        index page
  --mempool-info-timeout arg (=5000)    maximum time, in milliseconds, to wait
                                        for mempool data for the front page
  --mempool-refresh-time arg (=5)       time, in seconds, for each refresh of
                                        mempool state
  -b [ --bc-path ] arg                  path to lmdb folder of the blockchain,
                                        e.g., ~/.bitmonero/lmdb
  --ssl-crt-file arg                    path to crt file for ssl (https)
                                        functionality
  --ssl-key-file arg                    path to key file for ssl (https)
                                        functionality
  -d [ --deamon-url ] arg (=http:://127.0.0.1:8081)
                                        Safex deamon url
```

Example usage, defined as bash aliases.

```bash
# for mainnet explorer
alias xmrblocksmainnet='~/safex-blockchain-explorer/build/safex-explorer --port 8081 --testnet-url "http://127.0.0.1:8082" --enable-pusher --enable-emission-monitor'

# for testnet explorer
alias xmrblockstestnet='~/safex-blockchain-explorer/build/safex-explorer -t --port 8082 --mainnet-url "http://127.0.0.1:8081" --enable-pusher --enable-emission-monitor'
```

These are aliases similar to those used for http://127.0.0.1:8081/ and http://127.0.0.1:8082/, respectively.

//
// Created by mwo on 5/11/15.
//

#ifndef XMREG01_SAFEX_HEADERS_H_H
#define XMREG01_SAFEX_HEADERS_H_H

#define DB_LMDB   2
#define BLOCKCHAIN_DB DB_LMDB


#define UNSIGNED_TX_PREFIX "Safex unsigned tx set\003"
#define SIGNED_TX_PREFIX "Safex signed tx set\003"
#define KEY_IMAGE_EXPORT_FILE_MAGIC "Safex key image export\002"
#define OUTPUT_EXPORT_FILE_MAGIC "Safex output export\003"

#define FEE_ESTIMATE_GRACE_BLOCKS 10 // estimate fee valid for that many blocks

#include "version.h"

#include "net/http_client.h"
#include "storages/http_abstract_invoke.h"

#include "cryptonote_core/tx_pool.h"
#include "cryptonote_core/blockchain.h"
#include "blockchain_db/lmdb/db_lmdb.h"
#include "device/device_default.hpp"

#include "wallet/wallet.h"

#include "serialization/binary_utils.h"

#include "easylogging++.h"

#include "common/base58.h"

#include "string_coding.h"


#endif //XMREG01_SAFEX_HEADERS_H_H


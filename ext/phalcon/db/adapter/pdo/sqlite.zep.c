
#ifdef HAVE_CONFIG_H
#include "../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../php_ext.h"
#include "../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/hash.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 |          Rack Lin <racklin@gmail.com>                                  |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Db\Adapter\Pdo\Sqlite
 *
 * Specific functions for the Sqlite database system
 * <code>
 *
 * $config = array(
 *  "dbname" => "/tmp/test.sqlite"
 * );
 *
 * $connection = new \Phalcon\Db\Adapter\Pdo\Sqlite($config);
 *
 * </code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Adapter_Pdo_Sqlite) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Db\\Adapter\\Pdo, Sqlite, phalcon, db_adapter_pdo_sqlite, phalcon_db_adapter_pdo_ce, phalcon_db_adapter_pdo_sqlite_method_entry, 0);

	zend_declare_property_string(phalcon_db_adapter_pdo_sqlite_ce, SL("_type"), "sqlite", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(phalcon_db_adapter_pdo_sqlite_ce, SL("_dialectType"), "sqlite", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(phalcon_db_adapter_pdo_sqlite_ce TSRMLS_CC, 1, phalcon_db_adapterinterface_ce);
	return SUCCESS;

}

/**
 * This method is automatically called in Phalcon\Db\Adapter\Pdo constructor.
 * Call it when you need to restore a database connection.
 *
 * @param array $descriptor
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, connect) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *descriptor = NULL, *dbname;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &descriptor);

	if (!descriptor) {
		ZEPHIR_CPY_WRT(descriptor, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(descriptor);
	}


	if (Z_TYPE_P(descriptor) == IS_NULL) {
		ZEPHIR_OBS_NVAR(descriptor);
		zephir_read_property_this(&descriptor, this_ptr, SL("_descriptor"), PH_NOISY_CC);
	}
	if (!(zephir_array_isset_string(descriptor, SS("dbname")))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "dbname must be specified", "phalcon/db/adapter/pdo/sqlite.zep", 63);
		return;
	}
	ZEPHIR_OBS_VAR(dbname);
	zephir_array_isset_string_fetch(&dbname, descriptor, SS("dbname"), 0 TSRMLS_CC);
	zephir_array_update_string(&descriptor, SL("dsn"), &dbname, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_PARENT(NULL, phalcon_db_adapter_pdo_sqlite_ce, this_ptr, "connect", &_0, descriptor);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns an array of Phalcon\Db\Column objects describing a table
 *
 * <code>
 * print_r($connection->describeColumns("posts"));
 * </code>
 *
 * @param string table
 * @param string schema
 * @return Phalcon\Db\Column[]
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, describeColumns) {

	zephir_fcall_cache_entry *_15 = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_10 = NULL;
	HashTable *_5;
	HashPosition _4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *table_param = NULL, *schema_param = NULL, *columns, *columnType = NULL, *field = NULL, *definition = NULL, *oldColumn = NULL, *sizePattern, *matches = NULL, *matchOne = NULL, *matchTwo = NULL, *columnName, *attribute = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3 = NULL, **_6, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_11 = NULL, *_12, *_13, *_14 = NULL;
	zval *table = NULL, *schema = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &table_param, &schema_param);

	zephir_get_strval(table, table_param);
	if (!schema_param) {
		ZEPHIR_INIT_VAR(schema);
		ZVAL_EMPTY_STRING(schema);
	} else {
		zephir_get_strval(schema, schema_param);
	}


	ZEPHIR_INIT_VAR(oldColumn);
	ZVAL_NULL(oldColumn);
	ZEPHIR_INIT_VAR(sizePattern);
	ZVAL_STRING(sizePattern, "#\\(([0-9]+)(?:,\\s*([0-9]+))*\\)#", 1);
	ZEPHIR_INIT_VAR(columns);
	array_init(columns);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "describecolumns", NULL, table, schema);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchall", NULL, _2, _3);
	zephir_check_call_status();
	zephir_is_iterable(_0, &_5, &_4, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HVALUE(field, _6);
		ZEPHIR_INIT_NVAR(definition);
		array_init_size(definition, 2);
		add_assoc_long_ex(definition, SS("bindType"), 2);
		ZEPHIR_OBS_NVAR(columnType);
		zephir_array_fetch_long(&columnType, field, 2, PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 108 TSRMLS_CC);
		while (1) {
			if (zephir_memnstr_str(columnType, SL("tinyint(1)"), "phalcon/db/adapter/pdo/sqlite.zep", 115)) {
				ZEPHIR_INIT_NVAR(_3);
				ZVAL_LONG(_3, 8);
				zephir_array_update_string(&definition, SL("type"), &_3, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 5);
				zephir_array_update_string(&definition, SL("bindType"), &_7, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(columnType);
				ZVAL_STRING(columnType, "boolean", 1);
				break;
			}
			if (zephir_memnstr_str(columnType, SL("int"), "phalcon/db/adapter/pdo/sqlite.zep", 125)) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 0);
				zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(_8);
				ZVAL_LONG(_8, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_8, PH_COPY | PH_SEPARATE);
				ZEPHIR_OBS_NVAR(attribute);
				zephir_array_fetch_long(&attribute, field, 5, PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 129 TSRMLS_CC);
				if (ZEPHIR_IS_TRUE_IDENTICAL(attribute)) {
					zephir_array_update_string(&definition, SL("autoIncrement"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
				}
				break;
			}
			if (zephir_memnstr_str(columnType, SL("varchar"), "phalcon/db/adapter/pdo/sqlite.zep", 139)) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 2);
				zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
				break;
			}
			if (zephir_memnstr_str(columnType, SL("date"), "phalcon/db/adapter/pdo/sqlite.zep", 147)) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 1);
				zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
				break;
			}
			if (zephir_memnstr_str(columnType, SL("timestamp"), "phalcon/db/adapter/pdo/sqlite.zep", 155)) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 1);
				zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
				break;
			}
			if (zephir_memnstr_str(columnType, SL("decimal"), "phalcon/db/adapter/pdo/sqlite.zep", 163)) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 3);
				zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(_8);
				ZVAL_LONG(_8, 32);
				zephir_array_update_string(&definition, SL("bindType"), &_8, PH_COPY | PH_SEPARATE);
				break;
			}
			if (zephir_memnstr_str(columnType, SL("char"), "phalcon/db/adapter/pdo/sqlite.zep", 173)) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 5);
				zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
				break;
			}
			if (zephir_memnstr_str(columnType, SL("datetime"), "phalcon/db/adapter/pdo/sqlite.zep", 181)) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 4);
				zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
				break;
			}
			if (zephir_memnstr_str(columnType, SL("text"), "phalcon/db/adapter/pdo/sqlite.zep", 189)) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 6);
				zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
				break;
			}
			if (zephir_memnstr_str(columnType, SL("float"), "phalcon/db/adapter/pdo/sqlite.zep", 197)) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 7);
				zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(_8);
				ZVAL_LONG(_8, 3);
				zephir_array_update_string(&definition, SL("bindType"), &_8, PH_COPY | PH_SEPARATE);
				break;
			}
			if (zephir_memnstr_str(columnType, SL("enum"), "phalcon/db/adapter/pdo/sqlite.zep", 207)) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_LONG(_7, 5);
				zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
				break;
			}
			ZEPHIR_INIT_NVAR(_7);
			ZVAL_LONG(_7, 2);
			zephir_array_update_string(&definition, SL("type"), &_7, PH_COPY | PH_SEPARATE);
			break;
		}
		if (zephir_memnstr_str(columnType, SL("("), "phalcon/db/adapter/pdo/sqlite.zep", 222)) {
			ZEPHIR_INIT_NVAR(matches);
			ZVAL_NULL(matches);
			Z_SET_ISREF_P(matches);
			ZEPHIR_CALL_FUNCTION(&_9, "preg_match", &_10, sizePattern, columnType, matches);
			Z_UNSET_ISREF_P(matches);
			zephir_check_call_status();
			if (zephir_is_true(_9)) {
				ZEPHIR_OBS_NVAR(matchOne);
				if (zephir_array_isset_long_fetch(&matchOne, matches, 1, 0 TSRMLS_CC)) {
					ZEPHIR_INIT_NVAR(_8);
					ZVAL_LONG(_8, zephir_get_intval(matchOne));
					zephir_array_update_string(&definition, SL("size"), &_8, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(matchTwo);
				if (zephir_array_isset_long_fetch(&matchTwo, matches, 2, 0 TSRMLS_CC)) {
					ZEPHIR_INIT_NVAR(_11);
					ZVAL_LONG(_11, zephir_get_intval(matchTwo));
					zephir_array_update_string(&definition, SL("scale"), &_11, PH_COPY | PH_SEPARATE);
				}
			}
		}
		if (zephir_memnstr_str(columnType, SL("unsigned"), "phalcon/db/adapter/pdo/sqlite.zep", 237)) {
			zephir_array_update_string(&definition, SL("unsigned"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
		}
		if (Z_TYPE_P(oldColumn) == IS_NULL) {
			zephir_array_update_string(&definition, SL("first"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
		} else {
			zephir_array_update_string(&definition, SL("after"), &oldColumn, PH_COPY | PH_SEPARATE);
		}
		zephir_array_fetch_long(&_12, field, 5, PH_NOISY | PH_READONLY, "phalcon/db/adapter/pdo/sqlite.zep", 253 TSRMLS_CC);
		if (zephir_is_true(_12)) {
			zephir_array_update_string(&definition, SL("primary"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
		}
		zephir_array_fetch_long(&_13, field, 3, PH_NOISY | PH_READONLY, "phalcon/db/adapter/pdo/sqlite.zep", 260 TSRMLS_CC);
		if (zephir_is_true(_13)) {
			zephir_array_update_string(&definition, SL("notNull"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
		}
		zephir_array_fetch_long(&columnName, field, 1, PH_NOISY | PH_READONLY, "phalcon/db/adapter/pdo/sqlite.zep", 267 TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_14);
		object_init_ex(_14, phalcon_db_column_ce);
		ZEPHIR_CALL_METHOD(NULL, _14, "__construct", &_15, columnName, definition);
		zephir_check_call_status();
		zephir_array_append(&columns, _14, PH_SEPARATE, "phalcon/db/adapter/pdo/sqlite.zep", 268);
		ZEPHIR_CPY_WRT(oldColumn, columnName);
	}
	RETURN_CCTOR(columns);

}

/**
 * Lists table indexes
 *
 * @param	string table
 * @param	string schema
 * @return	Phalcon\Db\IndexInterface[]
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, describeIndexes) {

	zephir_fcall_cache_entry *_18 = NULL;
	HashTable *_5, *_11, *_15;
	HashPosition _4, _10, _14;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *table, *schema = NULL, *indexes, *index = NULL, *keyName = NULL, *indexObjects, *name = NULL, *indexColumns = NULL, *columns = NULL, *describe_index = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3 = NULL, **_6, *_7 = NULL, *_8, *_9 = NULL, **_12, *_13, **_16, *_17 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &table, &schema);

	if (!schema) {
		schema = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(indexes);
	array_init(indexes);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "describeindexes", NULL, table, schema);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchall", NULL, _2, _3);
	zephir_check_call_status();
	zephir_is_iterable(_0, &_5, &_4, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HVALUE(index, _6);
		ZEPHIR_OBS_NVAR(keyName);
		zephir_array_fetch_long(&keyName, index, 1, PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 290 TSRMLS_CC);
		if (!(zephir_array_isset(indexes, keyName))) {
			ZEPHIR_INIT_NVAR(columns);
			array_init(columns);
		} else {
			ZEPHIR_OBS_NVAR(columns);
			zephir_array_fetch(&columns, indexes, keyName, PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 294 TSRMLS_CC);
		}
		_8 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_9, _8, "describeindex", NULL, keyName);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, 3);
		ZEPHIR_CALL_METHOD(&_7, this_ptr, "fetchall", NULL, _9, _3);
		zephir_check_call_status();
		zephir_is_iterable(_7, &_11, &_10, 0, 0);
		for (
		  ; zephir_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
		  ; zephir_hash_move_forward_ex(_11, &_10)
		) {
			ZEPHIR_GET_HVALUE(describe_index, _12);
			zephir_array_fetch_long(&_13, describe_index, 2, PH_NOISY | PH_READONLY, "phalcon/db/adapter/pdo/sqlite.zep", 298 TSRMLS_CC);
			zephir_array_append(&columns, _13, PH_SEPARATE, "phalcon/db/adapter/pdo/sqlite.zep", 298);
		}
		zephir_array_update_zval(&indexes, keyName, &columns, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(indexObjects);
	array_init(indexObjects);
	zephir_is_iterable(indexes, &_15, &_14, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_15, (void**) &_16, &_14) == SUCCESS
	  ; zephir_hash_move_forward_ex(_15, &_14)
	) {
		ZEPHIR_GET_HMKEY(name, _15, _14);
		ZEPHIR_GET_HVALUE(indexColumns, _16);
		ZEPHIR_INIT_LNVAR(_17);
		object_init_ex(_17, phalcon_db_index_ce);
		ZEPHIR_CALL_METHOD(NULL, _17, "__construct", &_18, name, indexColumns);
		zephir_check_call_status();
		zephir_array_update_zval(&indexObjects, name, &_17, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(indexObjects);

}

/**
 * Lists table references
 *
 * @param	string table
 * @param	string schema
 * @return	Phalcon\Db\ReferenceInterface[]
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, describeReferences) {

	zephir_fcall_cache_entry *_17 = NULL;
	zval *_11 = NULL;
	HashTable *_5, *_13;
	HashPosition _4, _12;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *table, *schema = NULL, *references, *reference = NULL, *arrayReference = NULL, *constraintName = NULL, *referenceObjects, *name = NULL, *referencedSchema = NULL, *referencedTable = NULL, *columns = NULL, *referencedColumns = NULL, *number = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3, **_6, *_7, *_8, *_9, *_10, **_14, *_15 = NULL, *_16 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &table, &schema);

	if (!schema) {
		schema = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(references);
	array_init(references);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "describereferences", NULL, table, schema);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchall", NULL, _2, _3);
	zephir_check_call_status();
	zephir_is_iterable(_0, &_5, &_4, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HMKEY(number, _5, _4);
		ZEPHIR_GET_HVALUE(reference, _6);
		ZEPHIR_INIT_NVAR(constraintName);
		ZEPHIR_CONCAT_SV(constraintName, "foreign_key_", number);
		if (!(zephir_array_isset(references, constraintName))) {
			ZEPHIR_INIT_NVAR(referencedSchema);
			ZVAL_NULL(referencedSchema);
			ZEPHIR_OBS_NVAR(referencedTable);
			zephir_array_fetch_long(&referencedTable, reference, 2, PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 333 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(columns);
			array_init(columns);
			ZEPHIR_INIT_NVAR(referencedColumns);
			array_init(referencedColumns);
		} else {
			zephir_array_fetch(&_7, references, constraintName, PH_NOISY | PH_READONLY, "phalcon/db/adapter/pdo/sqlite.zep", 337 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(referencedSchema);
			zephir_array_fetch_string(&referencedSchema, _7, SL("referencedSchema"), PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 337 TSRMLS_CC);
			zephir_array_fetch(&_8, references, constraintName, PH_NOISY | PH_READONLY, "phalcon/db/adapter/pdo/sqlite.zep", 338 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(referencedTable);
			zephir_array_fetch_string(&referencedTable, _8, SL("referencedTable"), PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 338 TSRMLS_CC);
			zephir_array_fetch(&_9, references, constraintName, PH_NOISY | PH_READONLY, "phalcon/db/adapter/pdo/sqlite.zep", 339 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(columns);
			zephir_array_fetch_string(&columns, _9, SL("columns"), PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 339 TSRMLS_CC);
			zephir_array_fetch(&_10, references, constraintName, PH_NOISY | PH_READONLY, "phalcon/db/adapter/pdo/sqlite.zep", 340 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(referencedColumns);
			zephir_array_fetch_string(&referencedColumns, _10, SL("referencedColumns"), PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 340 TSRMLS_CC);
		}
		zephir_array_fetch_long(&_7, reference, 3, PH_NOISY | PH_READONLY, "phalcon/db/adapter/pdo/sqlite.zep", 343 TSRMLS_CC);
		zephir_array_append(&columns, _7, PH_SEPARATE, "phalcon/db/adapter/pdo/sqlite.zep", 343);
		zephir_array_fetch_long(&_8, reference, 4, PH_NOISY | PH_READONLY, "phalcon/db/adapter/pdo/sqlite.zep", 344 TSRMLS_CC);
		zephir_array_append(&referencedColumns, _8, PH_SEPARATE, "phalcon/db/adapter/pdo/sqlite.zep", 344);
		ZEPHIR_INIT_NVAR(_11);
		array_init_size(_11, 7);
		zephir_array_update_string(&_11, SL("referencedSchema"), &referencedSchema, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_11, SL("referencedTable"), &referencedTable, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_11, SL("columns"), &columns, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_11, SL("referencedColumns"), &referencedColumns, PH_COPY | PH_SEPARATE);
		zephir_array_update_zval(&references, constraintName, &_11, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(referenceObjects);
	array_init(referenceObjects);
	zephir_is_iterable(references, &_13, &_12, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_13, (void**) &_14, &_12) == SUCCESS
	  ; zephir_hash_move_forward_ex(_13, &_12)
	) {
		ZEPHIR_GET_HMKEY(name, _13, _12);
		ZEPHIR_GET_HVALUE(arrayReference, _14);
		ZEPHIR_INIT_LNVAR(_15);
		object_init_ex(_15, phalcon_db_reference_ce);
		ZEPHIR_INIT_NVAR(_11);
		array_init_size(_11, 7);
		ZEPHIR_OBS_NVAR(_16);
		zephir_array_fetch_string(&_16, arrayReference, SL("referencedSchema"), PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 357 TSRMLS_CC);
		zephir_array_update_string(&_11, SL("referencedSchema"), &_16, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_16);
		zephir_array_fetch_string(&_16, arrayReference, SL("referencedTable"), PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 358 TSRMLS_CC);
		zephir_array_update_string(&_11, SL("referencedTable"), &_16, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_16);
		zephir_array_fetch_string(&_16, arrayReference, SL("columns"), PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 359 TSRMLS_CC);
		zephir_array_update_string(&_11, SL("columns"), &_16, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_16);
		zephir_array_fetch_string(&_16, arrayReference, SL("referencedColumns"), PH_NOISY, "phalcon/db/adapter/pdo/sqlite.zep", 361 TSRMLS_CC);
		zephir_array_update_string(&_11, SL("referencedColumns"), &_16, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(NULL, _15, "__construct", &_17, name, _11);
		zephir_check_call_status();
		zephir_array_update_zval(&referenceObjects, name, &_15, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(referenceObjects);

}

/**
 * Check whether the database system requires an explicit value for identity columns
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, useExplicitIdValue) {


	RETURN_BOOL(1);

}


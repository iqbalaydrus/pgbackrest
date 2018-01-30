/***********************************************************************************************************************************
Test Key Value Data Type
***********************************************************************************************************************************/

/***********************************************************************************************************************************
Test Run
***********************************************************************************************************************************/
void testRun()
{
    // -----------------------------------------------------------------------------------------------------------------------------
    if (testBegin("kvNew() and kvFree()"))
    {
        KeyValue *store = NULL;

        TEST_ASSIGN(store, kvNew(), "new store");
        TEST_RESULT_PTR_NE(store->memContext, NULL, "mem context set");
        TEST_RESULT_PTR_NE(store->list, NULL, "list set");
        TEST_RESULT_INT(lstSize(store->list), 0, "list empty");

        TEST_RESULT_VOID(kvFree(store), "free store");
    }

    // -----------------------------------------------------------------------------------------------------------------------------
    if (testBegin("kvPut(), kvAdd(), kvKeyList(), kvGet(), kvGetList(), and kvDup()"))
    {
        KeyValue *store = NULL;

        TEST_ASSIGN(store, kvNew(), "new store");

        // Set various data types
        // -------------------------------------------------------------------------------------------------------------------------
        TEST_RESULT_PTR(kvPut(store, varNewStr(strNew("str-key")), varNewStr(strNew("str-value"))), store, "put string/string");
        TEST_RESULT_PTR(kvPut(store, varNewInt(42), varNewInt(57)), store, "put int/int");
        TEST_RESULT_PTR(kvPut(store, varNewStr(strNew("str-key-int")), varNewInt(99)), store, "put string/int");
        TEST_RESULT_PTR(kvPut(store, varNewInt(78), NULL), store, "put int/null");

        // Get the types and make sure they have the correct value
        // -------------------------------------------------------------------------------------------------------------------------
        TEST_RESULT_STR(strPtr(varStr(kvGet(store, varNewStr(strNew("str-key"))))), "str-value", "get string/string");
        TEST_RESULT_INT(varInt(kvGet(store, varNewInt(42))), 57, "get int/int");
        TEST_RESULT_INT(varInt(varLstGet(kvGetList(store, varNewInt(42)), 0)), 57, "get int/int");
        TEST_RESULT_INT(varInt(kvGet(store, varNewStr(strNew("str-key-int")))), 99, "get string/int");
        TEST_RESULT_PTR(kvGet(store, varNewInt(78)), NULL, "get int/null");

        // Check that a null value can be changed to non-null
        // -------------------------------------------------------------------------------------------------------------------------
        TEST_RESULT_PTR(kvPut(store, varNewInt(78), varNewInt(66)), store, "update int/null to int/int");
        TEST_RESULT_INT(varInt(kvGet(store, varNewInt(78))), 66, "get int/int");

        // Check that a value can be changed
        // -------------------------------------------------------------------------------------------------------------------------
        TEST_RESULT_PTR(kvPut(store, varNewInt(78), varNewBool(false)), store, "update int/int to int/bool");
        TEST_RESULT_INT(varBool(kvGet(store, varNewInt(78))), false, "get int/bool");

        // Use add to create variant list
        // -------------------------------------------------------------------------------------------------------------------------
        TEST_RESULT_PTR(kvAdd(store, varNewInt(99), NULL), store, "add int/null");
        TEST_RESULT_PTR(kvAdd(store, varNewInt(99), varNewInt(1)), store, "add int/int");
        TEST_RESULT_PTR(kvAdd(store, varNewInt(99), varNewInt(2)), store, "add int/int");
        TEST_RESULT_PTR(kvAdd(store, varNewInt(99), varNewInt(3)), store, "add int/int");

        TEST_RESULT_INT(varInt(varLstGet(varVarLst(kvGet(store, varNewInt(99))), 0)), 1, "get int/int");
        TEST_RESULT_INT(varInt(varLstGet(varVarLst(kvGet(store, varNewInt(99))), 1)), 2, "get int/int");
        TEST_RESULT_INT(varInt(varLstGet(varVarLst(kvGet(store, varNewInt(99))), 2)), 3, "get int/int");

        TEST_RESULT_INT(varInt(varLstGet(kvGetList(store, varNewInt(99)), 2)), 3, "get int/int");

        // Check item in key list
        // -------------------------------------------------------------------------------------------------------------------------
        TEST_RESULT_INT(varInt(varLstGet(kvKeyList(store), 1)), 42, "key list");

        // Create a new kv and add it to this kv
        // -------------------------------------------------------------------------------------------------------------------------
        KeyValue *storeSub = kvPutKv(store, varNewStr(strNew("kv-key")));

        kvPut(storeSub, varNewStr(strNew("str-sub-key")), varNewStr(strNew("str-sub-value")));
        TEST_RESULT_STR(
            strPtr(varStr(kvGet(varKv(kvGet(store, varNewStr(strNew("kv-key")))), varNewStr(strNew("str-sub-key"))))),
            "str-sub-value", "get string/kv");

        // Duplicate the kv
        // -------------------------------------------------------------------------------------------------------------------------
        KeyValue *storeDup = kvDup(store);

        TEST_RESULT_INT(varBool(kvGet(store, varNewInt(78))), false, "get int/bool");
        TEST_RESULT_INT(varInt(varLstGet(varVarLst(kvGet(store, varNewInt(99))), 2)), 3, "get int/int");
        TEST_RESULT_STR(
            strPtr(varStr(kvGet(varKv(kvGet(storeDup, varNewStr(strNew("kv-key")))), varNewStr(strNew("str-sub-key"))))),
            "str-sub-value", "get string/kv");

        TEST_RESULT_VOID(kvFree(storeDup), "free dup store");
        TEST_RESULT_VOID(kvFree(store), "free store");
    }
}
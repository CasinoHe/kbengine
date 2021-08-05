// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com

#ifndef KBE_ENTITY_TABLE_MYSQL_H
#define KBE_ENTITY_TABLE_MYSQL_H
#include "mysql/mysql.h"
#include "db_interface_mysql.h"
#include "common.h"
#include "common/common.h"
#include "common/singleton.h"
#include "helper/debug_helper.h"
#include "db_interface/entity_table.h"

namespace KBEngine { 

class ScriptDefModule;
class EntityTableMysql;

#define MYSQL_ENGINE_TYPE "InnoDB"

/*
	维锟斤拷entity锟斤拷锟斤拷锟捷匡拷锟斤拷械锟揭伙拷锟斤拷侄锟�
*/
class EntityTableItemMysqlBase : public EntityTableItem
{
public:
	EntityTableItemMysqlBase(std::string itemDBType, uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItem(itemDBType, datalength, flags),
	  mysqlItemtype_(mysqlItemtype)
	{
		// 锟斤拷录锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟矫碉拷锟斤拷锟叫憋拷锟�
		ALL_MYSQL_SET_FLAGS |= flags;

		memset(db_item_name_, 0, MAX_BUF);
	};

	virtual ~EntityTableItemMysqlBase()
	{
	};

	uint8 type() const{ return TABLE_ITEM_TYPE_UNKONWN; }

	/**
		锟斤拷始锟斤拷
	*/
	virtual bool initialize(const PropertyDescription* pPropertyDescription, 
		const DataType* pDataType, std::string name);

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL) = 0;

	/**
		锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	virtual bool writeItem(DBInterface* pdbi, DBID dbid, MemoryStream* s, ScriptDefModule* pModule){ return true; }

	/**
		锟斤拷询锟斤拷
	*/
	virtual bool queryTable(DBInterface* pdbi, DBID dbid, MemoryStream* s, ScriptDefModule* pModule){ return true; }

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	virtual void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID){};

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context) = 0;
	virtual void getReadSqlItem(mysql::DBContext& context) = 0;

	virtual void init_db_item_name(const char* exstrFlag = "");
	const char* db_item_name(){ return db_item_name_; }

	virtual bool isSameKey(std::string key){ return key == db_item_name(); }

protected:
	char db_item_name_[MAX_BUF];
	enum_field_types mysqlItemtype_;
};

class EntityTableItemMysql_DIGIT : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_DIGIT(std::string dataSType, std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype),
		  dataSType_(dataSType)
	{
	};

	virtual ~EntityTableItemMysql_DIGIT(){};

	uint8 type() const{ return TABLE_ITEM_TYPE_DIGIT; }

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);

protected:
	std::string dataSType_;
};

class EntityTableItemMysql_STRING : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_STRING(std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype)
	  {
	  }

	virtual ~EntityTableItemMysql_STRING(){};

	uint8 type() const{ return TABLE_ITEM_TYPE_STRING; }

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);
};

class EntityTableItemMysql_UNICODE : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_UNICODE(std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype)
	  {
	  }

	virtual ~EntityTableItemMysql_UNICODE(){};

	uint8 type() const{ return TABLE_ITEM_TYPE_UNICODE; }

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);
};

class EntityTableItemMysql_PYTHON : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_PYTHON(std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype)
	  {
	  }

	virtual ~EntityTableItemMysql_PYTHON(){};

	uint8 type() const{ return TABLE_ITEM_TYPE_PYTHON; }

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);
};

class EntityTableItemMysql_BLOB : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_BLOB(std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype)
	  {
	  }

	virtual ~EntityTableItemMysql_BLOB(){};

	uint8 type() const{ return TABLE_ITEM_TYPE_BLOB; }

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);
};

class EntityTableItemMysql_VECTOR2 : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_VECTOR2(std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype)
	  {
	  }

	virtual ~EntityTableItemMysql_VECTOR2(){};

	uint8 type() const{ return TABLE_ITEM_TYPE_VECTOR2; }
	
	virtual bool isSameKey(std::string key);

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);

	virtual void init_db_item_name(const char* exstrFlag = "")
	{
		for(int i=0; i<2; ++i)
			kbe_snprintf(db_item_names_[i], MAX_BUF, TABLE_ITEM_PERFIX"_%d_%s%s", i, exstrFlag, itemName());
	}

protected:
	char db_item_names_[2][MAX_BUF];
};

class EntityTableItemMysql_VECTOR3 : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_VECTOR3(std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype)
	  {
	  }

	virtual ~EntityTableItemMysql_VECTOR3(){};

	uint8 type() const{ return TABLE_ITEM_TYPE_VECTOR3; }

	virtual bool isSameKey(std::string key);

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);

	virtual void init_db_item_name(const char* exstrFlag = "")
	{
		for(int i=0; i<3; ++i)
			kbe_snprintf(db_item_names_[i], MAX_BUF, TABLE_ITEM_PERFIX"_%d_%s%s", i, exstrFlag, itemName());
	}

protected:
	char db_item_names_[3][MAX_BUF];
};

class EntityTableItemMysql_VECTOR4 : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_VECTOR4(std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype)
	  {
	  }

	virtual ~EntityTableItemMysql_VECTOR4(){};

	uint8 type() const{ return TABLE_ITEM_TYPE_VECTOR4; }

	virtual bool isSameKey(std::string key);

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);

	virtual void init_db_item_name(const char* exstrFlag = "")
	{
		for(int i=0; i<4; ++i)
			kbe_snprintf(db_item_names_[i], MAX_BUF, TABLE_ITEM_PERFIX"_%d_%s%s", i, exstrFlag, itemName());
	}

protected:
	char db_item_names_[4][MAX_BUF];
};

class EntityTableItemMysql_ENTITYCALL : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_ENTITYCALL(std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype)
	  {
	  }

	virtual ~EntityTableItemMysql_ENTITYCALL(){};

	uint8 type() const{ return TABLE_ITEM_TYPE_ENTITYCALL; }

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);
};

class EntityTableItemMysql_ARRAY : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_ARRAY(std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype),
	  pChildTable_(NULL)
	  {
	  }

	virtual ~EntityTableItemMysql_ARRAY(){};

	virtual bool isSameKey(std::string key);

	/**
		锟斤拷始锟斤拷
	*/
	virtual bool initialize(const PropertyDescription* pPropertyDescription, 
		const DataType* pDataType, std::string name);

	uint8 type() const{ return TABLE_ITEM_TYPE_FIXEDARRAY; }

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);

	virtual void init_db_item_name(const char* exstrFlag = "");

protected:
	EntityTable* pChildTable_;
};

class EntityTableItemMysql_FIXED_DICT : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_FIXED_DICT(std::string itemDBType, 
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype):
	  EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype)
	  {
	  }

	virtual ~EntityTableItemMysql_FIXED_DICT(){};

	typedef std::vector< std::pair< std::string, KBEShared_ptr<EntityTableItem> > > FIXEDDICT_KEYTYPES;

	uint8 type() const{ return TABLE_ITEM_TYPE_FIXEDDICT; }

	virtual bool isSameKey(std::string key);

	/**
		锟斤拷始锟斤拷
	*/
	virtual bool initialize(const PropertyDescription* pPropertyDescription, 
		const DataType* pDataType, std::string name);

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);

	virtual void init_db_item_name(const char* exstrFlag = "");

	uint32 getItemDatabaseLength(const std::string& name);

protected:
	EntityTableItemMysql_FIXED_DICT::FIXEDDICT_KEYTYPES			keyTypes_;		// 锟斤拷锟斤拷潭锟斤拷值锟斤拷锟侥革拷锟斤拷key锟斤拷锟斤拷锟斤拷
};


class EntityTableItemMysql_Component : public EntityTableItemMysqlBase
{
public:
	EntityTableItemMysql_Component(std::string itemDBType,
		uint32 datalength, uint32 flags, enum_field_types mysqlItemtype) :
		EntityTableItemMysqlBase(itemDBType, datalength, flags, mysqlItemtype),
		pChildTable_(NULL)
	{
	}

	virtual ~EntityTableItemMysql_Component() {};

	virtual bool isSameKey(std::string key);

	/**
		锟斤拷始锟斤拷
	*/
	virtual bool initialize(const PropertyDescription* pPropertyDescription,
		const DataType* pDataType, std::string name);

	uint8 type() const { return TABLE_ITEM_TYPE_COMPONENT; }

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi, void* pData = NULL);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);

	virtual void init_db_item_name(const char* exstrFlag = "");

protected:
	EntityTable* pChildTable_;
};


/*
	维锟斤拷entity锟斤拷锟斤拷锟捷匡拷锟叫的憋拷
*/
class EntityTableMysql : public EntityTable
{
public:
	EntityTableMysql(EntityTables* pEntityTables);
	virtual ~EntityTableMysql();
	
	/**
		锟斤拷始锟斤拷
	*/
	virtual bool initialize(ScriptDefModule* sm, std::string name);

	/**
		同锟斤拷entity锟斤拷锟斤拷锟斤拷锟捷匡拷锟斤拷
	*/
	virtual bool syncToDB(DBInterface* pdbi);

	/**
		同锟斤拷锟斤拷锟斤拷锟斤拷
	*/
	virtual bool syncIndexToDB(DBInterface* pdbi);

	/** 
		锟斤拷锟斤拷一锟斤拷锟斤拷item
	*/
	virtual EntityTableItem* createItem(std::string type, std::string defaultVal);

	DBID writeTable(DBInterface* pdbi, DBID dbid, int8 shouldAutoLoad, MemoryStream* s, ScriptDefModule* pModule);

	/**
		锟斤拷锟斤拷锟捷匡拷删锟斤拷entity
	*/
	bool removeEntity(DBInterface* pdbi, DBID dbid, ScriptDefModule* pModule);

	/**
		锟斤拷取锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	virtual bool queryTable(DBInterface* pdbi, DBID dbid, MemoryStream* s, ScriptDefModule* pModule);

	/**
		锟斤拷锟斤拷锟角凤拷锟皆讹拷锟斤拷锟斤拷
	*/
	virtual void entityShouldAutoLoad(DBInterface* pdbi, DBID dbid, bool shouldAutoLoad);

	/**
		锟斤拷询锟皆讹拷锟斤拷锟截碉拷实锟斤拷
	*/
	virtual void queryAutoLoadEntities(DBInterface* pdbi, ScriptDefModule* pModule, 
		ENTITY_ID start, ENTITY_ID end, std::vector<DBID>& outs);

	/**
		锟斤拷取某锟斤拷锟斤拷锟斤拷锟叫碉拷锟斤拷锟捷放碉拷锟斤拷锟斤拷
	*/
	void addToStream(MemoryStream* s, mysql::DBContext& context, DBID resultDBID);

	/**
		锟斤拷取锟斤拷要锟芥储锟侥憋拷锟斤拷锟斤拷 锟街讹拷锟斤拷锟斤拷转锟斤拷为sql锟芥储时锟斤拷锟街凤拷锟斤拷值
	*/
	virtual void getWriteSqlItem(DBInterface* pdbi, MemoryStream* s, mysql::DBContext& context);
	virtual void getReadSqlItem(mysql::DBContext& context);

	void init_db_item_name();

protected:
	
};


}

#ifdef CODE_INLINE
#include "entity_table_mysql.inl"
#endif
#endif // KBE_ENTITY_TABLE_MYSQL_H

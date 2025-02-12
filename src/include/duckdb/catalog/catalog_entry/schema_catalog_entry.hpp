//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog_entry/schema_catalog_entry.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/catalog/catalog_entry.hpp"
#include "duckdb/catalog/catalog_set.hpp"
#include "duckdb/parser/query_error_context.hpp"

namespace duckdb {
class ClientContext;

class StandardEntry;
class TableCatalogEntry;
class TableFunctionCatalogEntry;
class SequenceCatalogEntry;
class Serializer;
class Deserializer;

enum class OnCreateConflict : uint8_t;

struct AlterTableInfo;
struct CreateIndexInfo;
struct CreateFunctionInfo;
struct CreateCollationInfo;
struct CreateViewInfo;
struct BoundCreateTableInfo;
struct CreatePragmaFunctionInfo;
struct CreateSequenceInfo;
struct CreateSchemaInfo;
struct CreateTableFunctionInfo;
struct CreateCopyFunctionInfo;
struct CreateTypeInfo;

struct DropInfo;

//! A schema in the catalog
class SchemaCatalogEntry : public CatalogEntry {
public:
	static constexpr const CatalogType Type = CatalogType::SCHEMA_ENTRY;
	static constexpr const char *Name = "schema";

public:
	SchemaCatalogEntry(Catalog *catalog, string name, bool is_internal);

public:
	//! Scan the specified catalog set, invoking the callback method for every entry
	virtual void Scan(ClientContext &context, CatalogType type,
	                  const std::function<void(CatalogEntry *)> &callback) = 0;
	//! Scan the specified catalog set, invoking the callback method for every committed entry
	virtual void Scan(CatalogType type, const std::function<void(CatalogEntry *)> &callback) = 0;

	//! Serialize the meta information of the SchemaCatalogEntry a serializer
	virtual void Serialize(Serializer &serializer) const;
	//! Deserializes to a CreateSchemaInfo
	static unique_ptr<CreateSchemaInfo> Deserialize(Deserializer &source);

	string ToSQL() const override;

	//! Creates an index with the given name in the schema
	virtual CatalogEntry *CreateIndex(ClientContext &context, CreateIndexInfo *info, TableCatalogEntry *table) = 0;
	//! Create a scalar or aggregate function within the given schema
	virtual CatalogEntry *CreateFunction(CatalogTransaction transaction, CreateFunctionInfo *info) = 0;
	//! Creates a table with the given name in the schema
	virtual CatalogEntry *CreateTable(CatalogTransaction transaction, BoundCreateTableInfo *info) = 0;
	//! Creates a view with the given name in the schema
	virtual CatalogEntry *CreateView(CatalogTransaction transaction, CreateViewInfo *info) = 0;
	//! Creates a sequence with the given name in the schema
	virtual CatalogEntry *CreateSequence(CatalogTransaction transaction, CreateSequenceInfo *info) = 0;
	//! Create a table function within the given schema
	virtual CatalogEntry *CreateTableFunction(CatalogTransaction transaction, CreateTableFunctionInfo *info) = 0;
	//! Create a copy function within the given schema
	virtual CatalogEntry *CreateCopyFunction(CatalogTransaction transaction, CreateCopyFunctionInfo *info) = 0;
	//! Create a pragma function within the given schema
	virtual CatalogEntry *CreatePragmaFunction(CatalogTransaction transaction, CreatePragmaFunctionInfo *info) = 0;
	//! Create a collation within the given schema
	virtual CatalogEntry *CreateCollation(CatalogTransaction transaction, CreateCollationInfo *info) = 0;
	//! Create a enum within the given schema
	virtual CatalogEntry *CreateType(CatalogTransaction transaction, CreateTypeInfo *info) = 0;

	DUCKDB_API virtual CatalogEntry *GetEntry(CatalogTransaction transaction, CatalogType type, const string &name) = 0;
	DUCKDB_API virtual SimilarCatalogEntry GetSimilarEntry(CatalogTransaction transaction, CatalogType type,
	                                                       const string &name);

	//! Drops an entry from the schema
	virtual void DropEntry(ClientContext &context, DropInfo *info) = 0;

	//! Alters a catalog entry
	virtual void Alter(ClientContext &context, AlterInfo *info) = 0;

	CatalogTransaction GetCatalogTransaction(ClientContext &context);
};
} // namespace duckdb

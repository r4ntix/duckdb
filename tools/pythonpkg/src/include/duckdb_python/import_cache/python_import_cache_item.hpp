//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb_python/import_cache/python_import_cache_item.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb_python/pybind_wrapper.hpp"
#include "duckdb.hpp"
#include "duckdb/common/vector.hpp"
#include "duckdb_python/python_object_container.hpp"

namespace duckdb {

struct PythonImportCache;

struct PythonImportCacheItem {
public:
	PythonImportCacheItem() : load_succeeded(false), object(nullptr) {
	}
	virtual ~PythonImportCacheItem() {
	}
	virtual void LoadSubtypes(PythonImportCache &cache) {
	}

public:
	bool LoadSucceeded() const;
	bool IsLoaded() const;
	bool IsInstance(py::handle object) const;
	py::handle operator()(void) const;
	void LoadModule(const string &name, PythonImportCache &cache);
	void LoadAttribute(const string &name, PythonImportCache &cache, PythonImportCacheItem &source);

protected:
	virtual bool IsRequired() const {
		return true;
	}

private:
	PyObject *AddCache(PythonImportCache &cache, py::object object);

private:
	//! Whether or not we attempted to load the module
	bool load_succeeded;
	//! The stored item
	PyObject *object;
};

} // namespace duckdb

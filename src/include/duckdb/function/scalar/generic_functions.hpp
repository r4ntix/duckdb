//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/scalar/generic_functions.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/function/scalar_function.hpp"
#include "duckdb/function/function_set.hpp"
#include "duckdb/function/built_in_functions.hpp"

namespace duckdb {
class BoundFunctionExpression;

struct AliasFun {
	static void RegisterFunction(BuiltinFunctions &set);
};

struct HashFun {
	static void RegisterFunction(BuiltinFunctions &set);
};

struct LeastFun {
	static void RegisterFunction(BuiltinFunctions &set);
};

struct GreatestFun {
	static void RegisterFunction(BuiltinFunctions &set);
};

struct StatsFun {
	static void RegisterFunction(BuiltinFunctions &set);
};

struct TypeOfFun {
	static void RegisterFunction(BuiltinFunctions &set);
};

struct ErrorFun {
	static void RegisterFunction(BuiltinFunctions &set);
};

struct ConstantOrNull {
	static ScalarFunction GetFunction(const LogicalType &return_type);
	static unique_ptr<FunctionData> Bind(Value value);
	static bool IsConstantOrNull(BoundFunctionExpression &expr, const Value &val);
	static void RegisterFunction(BuiltinFunctions &set);
};

struct CurrentSettingFun {
	static void RegisterFunction(BuiltinFunctions &set);
};

struct SystemFun {
	static void RegisterFunction(BuiltinFunctions &set);
};

struct ExportAggregateFunctionBindData : public FunctionData {
	unique_ptr<BoundAggregateExpression> aggregate;
	explicit ExportAggregateFunctionBindData(unique_ptr<Expression> aggregate_p);
	unique_ptr<FunctionData> Copy() const override;
	bool Equals(const FunctionData &other_p) const override;
};

struct ExportAggregateFunction {
	static unique_ptr<BoundAggregateExpression> Bind(unique_ptr<BoundAggregateExpression> child_aggregate);
	static ScalarFunction GetCombine();
	static ScalarFunction GetFinalize();
};

} // namespace duckdb

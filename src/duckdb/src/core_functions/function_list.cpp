#include "duckdb/core_functions/function_list.hpp"
#include "duckdb/core_functions/aggregate/algebraic_functions.hpp"
#include "duckdb/core_functions/aggregate/distributive_functions.hpp"
#include "duckdb/core_functions/aggregate/holistic_functions.hpp"
#include "duckdb/core_functions/aggregate/nested_functions.hpp"
#include "duckdb/core_functions/aggregate/regression_functions.hpp"
#include "duckdb/core_functions/scalar/bit_functions.hpp"
#include "duckdb/core_functions/scalar/blob_functions.hpp"
#include "duckdb/core_functions/scalar/date_functions.hpp"
#include "duckdb/core_functions/scalar/enum_functions.hpp"
#include "duckdb/core_functions/scalar/generic_functions.hpp"
#include "duckdb/core_functions/scalar/list_functions.hpp"
#include "duckdb/core_functions/scalar/map_functions.hpp"
#include "duckdb/core_functions/scalar/math_functions.hpp"
#include "duckdb/core_functions/scalar/operators_functions.hpp"
#include "duckdb/core_functions/scalar/random_functions.hpp"
#include "duckdb/core_functions/scalar/string_functions.hpp"
#include "duckdb/core_functions/scalar/struct_functions.hpp"
#include "duckdb/core_functions/scalar/union_functions.hpp"

namespace duckdb {

// Scalar Function
#define DUCKDB_SCALAR_FUNCTION_BASE(_PARAM, _NAME)                                                                     \
	{ _NAME, _PARAM::Parameters, _PARAM::Description, _PARAM::Example, _PARAM::GetFunction, nullptr, nullptr, nullptr }
#define DUCKDB_SCALAR_FUNCTION(_PARAM)       DUCKDB_SCALAR_FUNCTION_BASE(_PARAM, _PARAM::Name)
#define DUCKDB_SCALAR_FUNCTION_ALIAS(_PARAM) DUCKDB_SCALAR_FUNCTION_BASE(_PARAM::ALIAS, _PARAM::Name)
// Scalar Function Set
#define DUCKDB_SCALAR_FUNCTION_SET_BASE(_PARAM, _NAME)                                                                 \
	{ _NAME, _PARAM::Parameters, _PARAM::Description, _PARAM::Example, nullptr, _PARAM::GetFunctions, nullptr, nullptr }
#define DUCKDB_SCALAR_FUNCTION_SET(_PARAM)       DUCKDB_SCALAR_FUNCTION_SET_BASE(_PARAM, _PARAM::Name)
#define DUCKDB_SCALAR_FUNCTION_SET_ALIAS(_PARAM) DUCKDB_SCALAR_FUNCTION_SET_BASE(_PARAM::ALIAS, _PARAM::Name)
// Aggregate Function
#define DUCKDB_AGGREGATE_FUNCTION_BASE(_PARAM, _NAME)                                                                  \
	{ _NAME, _PARAM::Parameters, _PARAM::Description, _PARAM::Example, nullptr, nullptr, _PARAM::GetFunction, nullptr }
#define DUCKDB_AGGREGATE_FUNCTION(_PARAM)       DUCKDB_AGGREGATE_FUNCTION_BASE(_PARAM, _PARAM::Name)
#define DUCKDB_AGGREGATE_FUNCTION_ALIAS(_PARAM) DUCKDB_AGGREGATE_FUNCTION_BASE(_PARAM::ALIAS, _PARAM::Name)
// Aggregate Function Set
#define DUCKDB_AGGREGATE_FUNCTION_SET_BASE(_PARAM, _NAME)                                                              \
	{ _NAME, _PARAM::Parameters, _PARAM::Description, _PARAM::Example, nullptr, nullptr, nullptr, _PARAM::GetFunctions }
#define DUCKDB_AGGREGATE_FUNCTION_SET(_PARAM)       DUCKDB_AGGREGATE_FUNCTION_SET_BASE(_PARAM, _PARAM::Name)
#define DUCKDB_AGGREGATE_FUNCTION_SET_ALIAS(_PARAM) DUCKDB_AGGREGATE_FUNCTION_SET_BASE(_PARAM::ALIAS, _PARAM::Name)
#define FINAL_FUNCTION                                                                                                 \
	{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }

// this list is generated by scripts/generate_functions.py
static StaticFunctionDefinition internal_functions[] = {
	DUCKDB_SCALAR_FUNCTION(FactorialOperatorFun),
	DUCKDB_SCALAR_FUNCTION_SET(BitwiseAndFun),
	DUCKDB_SCALAR_FUNCTION(PowOperatorFun),
	DUCKDB_SCALAR_FUNCTION_SET(LeftShiftFun),
	DUCKDB_SCALAR_FUNCTION_SET(RightShiftFun),
	DUCKDB_SCALAR_FUNCTION_SET(AbsOperatorFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(PowOperatorFunAlias),
	DUCKDB_SCALAR_FUNCTION(StartsWithOperatorFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(AbsFun),
	DUCKDB_SCALAR_FUNCTION(AcosFun),
	DUCKDB_SCALAR_FUNCTION_SET(AgeFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(AggregateFun),
	DUCKDB_SCALAR_FUNCTION(AliasFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ApplyFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(ApproxCountDistinctFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(ApproxQuantileFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(ArgMaxFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(ArgMinFun),
	DUCKDB_AGGREGATE_FUNCTION_SET_ALIAS(ArgmaxFun),
	DUCKDB_AGGREGATE_FUNCTION_SET_ALIAS(ArgminFun),
	DUCKDB_AGGREGATE_FUNCTION_ALIAS(ArrayAggFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ArrayAggrFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ArrayAggregateFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ArrayApplyFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ArrayDistinctFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ArrayFilterFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(ArrayReverseSortFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ArraySliceFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(ArraySortFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ArrayTransformFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ArrayUniqueFun),
	DUCKDB_SCALAR_FUNCTION(ASCIIFun),
	DUCKDB_SCALAR_FUNCTION(AsinFun),
	DUCKDB_SCALAR_FUNCTION(AtanFun),
	DUCKDB_SCALAR_FUNCTION(Atan2Fun),
	DUCKDB_AGGREGATE_FUNCTION_SET(AvgFun),
	DUCKDB_SCALAR_FUNCTION_SET(BarFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(Base64Fun),
	DUCKDB_SCALAR_FUNCTION_SET(BinFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(BitAndFun),
	DUCKDB_SCALAR_FUNCTION_SET(BitCountFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(BitOrFun),
	DUCKDB_SCALAR_FUNCTION(BitPositionFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(BitXorFun),
	DUCKDB_SCALAR_FUNCTION(BitStringFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(BitstringAggFun),
	DUCKDB_AGGREGATE_FUNCTION(BoolAndFun),
	DUCKDB_AGGREGATE_FUNCTION(BoolOrFun),
	DUCKDB_SCALAR_FUNCTION(CardinalityFun),
	DUCKDB_SCALAR_FUNCTION(CbrtFun),
	DUCKDB_SCALAR_FUNCTION_SET(CeilFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(CeilingFun),
	DUCKDB_SCALAR_FUNCTION_SET(CenturyFun),
	DUCKDB_SCALAR_FUNCTION(ChrFun),
	DUCKDB_AGGREGATE_FUNCTION(CorrFun),
	DUCKDB_SCALAR_FUNCTION(CosFun),
	DUCKDB_SCALAR_FUNCTION(CotFun),
	DUCKDB_AGGREGATE_FUNCTION(CovarPopFun),
	DUCKDB_AGGREGATE_FUNCTION(CovarSampFun),
	DUCKDB_SCALAR_FUNCTION(CurrentDatabaseFun),
	DUCKDB_SCALAR_FUNCTION(CurrentDateFun),
	DUCKDB_SCALAR_FUNCTION(CurrentQueryFun),
	DUCKDB_SCALAR_FUNCTION(CurrentSchemaFun),
	DUCKDB_SCALAR_FUNCTION(CurrentSchemasFun),
	DUCKDB_SCALAR_FUNCTION(CurrentSettingFun),
	DUCKDB_SCALAR_FUNCTION(DamerauLevenshteinFun),
	DUCKDB_SCALAR_FUNCTION_SET(DateDiffFun),
	DUCKDB_SCALAR_FUNCTION_SET(DatePartFun),
	DUCKDB_SCALAR_FUNCTION_SET(DateSubFun),
	DUCKDB_SCALAR_FUNCTION_SET(DateTruncFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(DatediffFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(DatepartFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(DatesubFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(DatetruncFun),
	DUCKDB_SCALAR_FUNCTION_SET(DayFun),
	DUCKDB_SCALAR_FUNCTION_SET(DayNameFun),
	DUCKDB_SCALAR_FUNCTION_SET(DayOfMonthFun),
	DUCKDB_SCALAR_FUNCTION_SET(DayOfWeekFun),
	DUCKDB_SCALAR_FUNCTION_SET(DayOfYearFun),
	DUCKDB_SCALAR_FUNCTION_SET(DecadeFun),
	DUCKDB_SCALAR_FUNCTION(DecodeFun),
	DUCKDB_SCALAR_FUNCTION(DegreesFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(Editdist3Fun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ElementAtFun),
	DUCKDB_SCALAR_FUNCTION(EncodeFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(EntropyFun),
	DUCKDB_SCALAR_FUNCTION(EnumCodeFun),
	DUCKDB_SCALAR_FUNCTION(EnumFirstFun),
	DUCKDB_SCALAR_FUNCTION(EnumLastFun),
	DUCKDB_SCALAR_FUNCTION(EnumRangeFun),
	DUCKDB_SCALAR_FUNCTION(EnumRangeBoundaryFun),
	DUCKDB_SCALAR_FUNCTION_SET(EpochFun),
	DUCKDB_SCALAR_FUNCTION(EpochMsFun),
	DUCKDB_SCALAR_FUNCTION_SET(EraFun),
	DUCKDB_SCALAR_FUNCTION(ErrorFun),
	DUCKDB_SCALAR_FUNCTION(EvenFun),
	DUCKDB_SCALAR_FUNCTION(ExpFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(FactorialFun),
	DUCKDB_AGGREGATE_FUNCTION(FAvgFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(FilterFun),
	DUCKDB_SCALAR_FUNCTION(ListFlattenFun),
	DUCKDB_SCALAR_FUNCTION_SET(FloorFun),
	DUCKDB_SCALAR_FUNCTION(FormatFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(FormatreadabledecimalsizeFun),
	DUCKDB_SCALAR_FUNCTION(FormatBytesFun),
	DUCKDB_SCALAR_FUNCTION(FromBase64Fun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(FromBinaryFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(FromHexFun),
	DUCKDB_AGGREGATE_FUNCTION_ALIAS(FsumFun),
	DUCKDB_SCALAR_FUNCTION(GammaFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(GcdFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(GenRandomUuidFun),
	DUCKDB_SCALAR_FUNCTION_SET(GenerateSeriesFun),
	DUCKDB_SCALAR_FUNCTION(GetBitFun),
	DUCKDB_SCALAR_FUNCTION(CurrentTimeFun),
	DUCKDB_SCALAR_FUNCTION(GetCurrentTimestampFun),
	DUCKDB_SCALAR_FUNCTION_SET(GreatestFun),
	DUCKDB_SCALAR_FUNCTION_SET(GreatestCommonDivisorFun),
	DUCKDB_AGGREGATE_FUNCTION_SET_ALIAS(GroupConcatFun),
	DUCKDB_SCALAR_FUNCTION(HammingFun),
	DUCKDB_SCALAR_FUNCTION(HashFun),
	DUCKDB_SCALAR_FUNCTION_SET(HexFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(HistogramFun),
	DUCKDB_SCALAR_FUNCTION_SET(HoursFun),
	DUCKDB_SCALAR_FUNCTION(InSearchPathFun),
	DUCKDB_SCALAR_FUNCTION(InstrFun),
	DUCKDB_SCALAR_FUNCTION_SET(IsFiniteFun),
	DUCKDB_SCALAR_FUNCTION_SET(IsInfiniteFun),
	DUCKDB_SCALAR_FUNCTION_SET(IsNanFun),
	DUCKDB_SCALAR_FUNCTION_SET(ISODayOfWeekFun),
	DUCKDB_SCALAR_FUNCTION_SET(ISOYearFun),
	DUCKDB_SCALAR_FUNCTION(JaccardFun),
	DUCKDB_SCALAR_FUNCTION(JaroSimilarityFun),
	DUCKDB_SCALAR_FUNCTION(JaroWinklerSimilarityFun),
	DUCKDB_AGGREGATE_FUNCTION(KahanSumFun),
	DUCKDB_AGGREGATE_FUNCTION(KurtosisFun),
	DUCKDB_SCALAR_FUNCTION_SET(LastDayFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(LcmFun),
	DUCKDB_SCALAR_FUNCTION_SET(LeastFun),
	DUCKDB_SCALAR_FUNCTION_SET(LeastCommonMultipleFun),
	DUCKDB_SCALAR_FUNCTION(LeftFun),
	DUCKDB_SCALAR_FUNCTION(LeftGraphemeFun),
	DUCKDB_SCALAR_FUNCTION(LevenshteinFun),
	DUCKDB_SCALAR_FUNCTION(LogGammaFun),
	DUCKDB_AGGREGATE_FUNCTION(ListFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ListAggrFun),
	DUCKDB_SCALAR_FUNCTION(ListAggregateFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ListApplyFun),
	DUCKDB_SCALAR_FUNCTION(ListDistinctFun),
	DUCKDB_SCALAR_FUNCTION(ListFilterFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(ListPackFun),
	DUCKDB_SCALAR_FUNCTION_SET(ListReverseSortFun),
	DUCKDB_SCALAR_FUNCTION(ListSliceFun),
	DUCKDB_SCALAR_FUNCTION_SET(ListSortFun),
	DUCKDB_SCALAR_FUNCTION(ListTransformFun),
	DUCKDB_SCALAR_FUNCTION(ListUniqueFun),
	DUCKDB_SCALAR_FUNCTION(ListValueFun),
	DUCKDB_SCALAR_FUNCTION(LnFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(LogFun),
	DUCKDB_SCALAR_FUNCTION(Log10Fun),
	DUCKDB_SCALAR_FUNCTION(Log2Fun),
	DUCKDB_SCALAR_FUNCTION(LpadFun),
	DUCKDB_SCALAR_FUNCTION_SET(LtrimFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(MadFun),
	DUCKDB_SCALAR_FUNCTION_SET(MakeDateFun),
	DUCKDB_SCALAR_FUNCTION(MakeTimeFun),
	DUCKDB_SCALAR_FUNCTION(MakeTimestampFun),
	DUCKDB_SCALAR_FUNCTION(MapFun),
	DUCKDB_SCALAR_FUNCTION(MapConcatFun),
	DUCKDB_SCALAR_FUNCTION(MapEntriesFun),
	DUCKDB_SCALAR_FUNCTION(MapExtractFun),
	DUCKDB_SCALAR_FUNCTION(MapFromEntriesFun),
	DUCKDB_SCALAR_FUNCTION(MapKeysFun),
	DUCKDB_SCALAR_FUNCTION(MapValuesFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(MaxFun),
	DUCKDB_AGGREGATE_FUNCTION_SET_ALIAS(MaxByFun),
	DUCKDB_SCALAR_FUNCTION(MD5Fun),
	DUCKDB_SCALAR_FUNCTION(MD5NumberFun),
	DUCKDB_SCALAR_FUNCTION(MD5NumberLowerFun),
	DUCKDB_SCALAR_FUNCTION(MD5NumberUpperFun),
	DUCKDB_AGGREGATE_FUNCTION_SET_ALIAS(MeanFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(MedianFun),
	DUCKDB_SCALAR_FUNCTION_SET(MicrosecondsFun),
	DUCKDB_SCALAR_FUNCTION_SET(MillenniumFun),
	DUCKDB_SCALAR_FUNCTION_SET(MillisecondsFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(MinFun),
	DUCKDB_AGGREGATE_FUNCTION_SET_ALIAS(MinByFun),
	DUCKDB_SCALAR_FUNCTION_SET(MinutesFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(MismatchesFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(ModeFun),
	DUCKDB_SCALAR_FUNCTION_SET(MonthFun),
	DUCKDB_SCALAR_FUNCTION_SET(MonthNameFun),
	DUCKDB_SCALAR_FUNCTION_SET(NextAfterFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(NowFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(OrdFun),
	DUCKDB_SCALAR_FUNCTION(PiFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(PositionFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(PowFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(PowerFun),
	DUCKDB_SCALAR_FUNCTION(PrintfFun),
	DUCKDB_AGGREGATE_FUNCTION(ProductFun),
	DUCKDB_AGGREGATE_FUNCTION_SET_ALIAS(QuantileFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(QuantileContFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(QuantileDiscFun),
	DUCKDB_SCALAR_FUNCTION_SET(QuarterFun),
	DUCKDB_SCALAR_FUNCTION(RadiansFun),
	DUCKDB_SCALAR_FUNCTION(RandomFun),
	DUCKDB_SCALAR_FUNCTION_SET(ListRangeFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(RegexpSplitToArrayFun),
	DUCKDB_AGGREGATE_FUNCTION(RegrAvgxFun),
	DUCKDB_AGGREGATE_FUNCTION(RegrAvgyFun),
	DUCKDB_AGGREGATE_FUNCTION(RegrCountFun),
	DUCKDB_AGGREGATE_FUNCTION(RegrInterceptFun),
	DUCKDB_AGGREGATE_FUNCTION(RegrR2Fun),
	DUCKDB_AGGREGATE_FUNCTION(RegrSlopeFun),
	DUCKDB_AGGREGATE_FUNCTION(RegrSXXFun),
	DUCKDB_AGGREGATE_FUNCTION(RegrSXYFun),
	DUCKDB_AGGREGATE_FUNCTION(RegrSYYFun),
	DUCKDB_SCALAR_FUNCTION(RepeatFun),
	DUCKDB_SCALAR_FUNCTION(ReplaceFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(ReservoirQuantileFun),
	DUCKDB_SCALAR_FUNCTION(ReverseFun),
	DUCKDB_SCALAR_FUNCTION(RightFun),
	DUCKDB_SCALAR_FUNCTION(RightGraphemeFun),
	DUCKDB_SCALAR_FUNCTION_SET(RoundFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(RowFun),
	DUCKDB_SCALAR_FUNCTION(RpadFun),
	DUCKDB_SCALAR_FUNCTION_SET(RtrimFun),
	DUCKDB_SCALAR_FUNCTION_SET(SecondsFun),
	DUCKDB_AGGREGATE_FUNCTION(StandardErrorOfTheMeanFun),
	DUCKDB_SCALAR_FUNCTION(SetBitFun),
	DUCKDB_SCALAR_FUNCTION(SetseedFun),
	DUCKDB_SCALAR_FUNCTION_SET(SignFun),
	DUCKDB_SCALAR_FUNCTION_SET(SignBitFun),
	DUCKDB_SCALAR_FUNCTION(SinFun),
	DUCKDB_AGGREGATE_FUNCTION(SkewnessFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(SplitFun),
	DUCKDB_SCALAR_FUNCTION(SqrtFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(StartsWithFun),
	DUCKDB_SCALAR_FUNCTION(StatsFun),
	DUCKDB_AGGREGATE_FUNCTION_ALIAS(StddevFun),
	DUCKDB_AGGREGATE_FUNCTION(StdDevPopFun),
	DUCKDB_AGGREGATE_FUNCTION(StdDevSampFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(StrSplitFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(StrSplitRegexFun),
	DUCKDB_SCALAR_FUNCTION_SET(StrfTimeFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(StringAggFun),
	DUCKDB_SCALAR_FUNCTION(StringSplitFun),
	DUCKDB_SCALAR_FUNCTION_SET(StringSplitRegexFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(StringToArrayFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(StrposFun),
	DUCKDB_SCALAR_FUNCTION_SET(StrpTimeFun),
	DUCKDB_SCALAR_FUNCTION(StructInsertFun),
	DUCKDB_SCALAR_FUNCTION(StructPackFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(SumFun),
	DUCKDB_AGGREGATE_FUNCTION_SET(SumNoOverflowFun),
	DUCKDB_AGGREGATE_FUNCTION_ALIAS(SumkahanFun),
	DUCKDB_SCALAR_FUNCTION(TanFun),
	DUCKDB_SCALAR_FUNCTION_SET(TimeBucketFun),
	DUCKDB_SCALAR_FUNCTION_SET(TimezoneFun),
	DUCKDB_SCALAR_FUNCTION_SET(TimezoneHourFun),
	DUCKDB_SCALAR_FUNCTION_SET(TimezoneMinuteFun),
	DUCKDB_SCALAR_FUNCTION(ToBase64Fun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(ToBinaryFun),
	DUCKDB_SCALAR_FUNCTION(ToDaysFun),
	DUCKDB_SCALAR_FUNCTION_SET_ALIAS(ToHexFun),
	DUCKDB_SCALAR_FUNCTION(ToHoursFun),
	DUCKDB_SCALAR_FUNCTION(ToMicrosecondsFun),
	DUCKDB_SCALAR_FUNCTION(ToMillisecondsFun),
	DUCKDB_SCALAR_FUNCTION(ToMinutesFun),
	DUCKDB_SCALAR_FUNCTION(ToMonthsFun),
	DUCKDB_SCALAR_FUNCTION(ToSecondsFun),
	DUCKDB_SCALAR_FUNCTION(ToTimestampFun),
	DUCKDB_SCALAR_FUNCTION(ToYearsFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(TodayFun),
	DUCKDB_SCALAR_FUNCTION_ALIAS(TransactionTimestampFun),
	DUCKDB_SCALAR_FUNCTION(TranslateFun),
	DUCKDB_SCALAR_FUNCTION_SET(TrimFun),
	DUCKDB_SCALAR_FUNCTION_SET(TruncFun),
	DUCKDB_SCALAR_FUNCTION_SET(TryStrpTimeFun),
	DUCKDB_SCALAR_FUNCTION(CurrentTransactionIdFun),
	DUCKDB_SCALAR_FUNCTION(TypeOfFun),
	DUCKDB_SCALAR_FUNCTION(UnbinFun),
	DUCKDB_SCALAR_FUNCTION(UnhexFun),
	DUCKDB_SCALAR_FUNCTION(UnicodeFun),
	DUCKDB_SCALAR_FUNCTION(UnionExtractFun),
	DUCKDB_SCALAR_FUNCTION(UnionTagFun),
	DUCKDB_SCALAR_FUNCTION(UnionValueFun),
	DUCKDB_SCALAR_FUNCTION(UUIDFun),
	DUCKDB_AGGREGATE_FUNCTION(VarPopFun),
	DUCKDB_AGGREGATE_FUNCTION(VarSampFun),
	DUCKDB_AGGREGATE_FUNCTION_ALIAS(VarianceFun),
	DUCKDB_SCALAR_FUNCTION(VersionFun),
	DUCKDB_SCALAR_FUNCTION_SET(WeekFun),
	DUCKDB_SCALAR_FUNCTION_SET(WeekDayFun),
	DUCKDB_SCALAR_FUNCTION_SET(WeekOfYearFun),
	DUCKDB_SCALAR_FUNCTION_SET(BitwiseXorFun),
	DUCKDB_SCALAR_FUNCTION_SET(YearFun),
	DUCKDB_SCALAR_FUNCTION_SET(YearWeekFun),
	DUCKDB_SCALAR_FUNCTION_SET(BitwiseOrFun),
	DUCKDB_SCALAR_FUNCTION_SET(BitwiseNotFun),
	FINAL_FUNCTION
};

StaticFunctionDefinition *StaticFunctionDefinition::GetFunctionList() {
	return internal_functions;
}

} // namespace duckdb

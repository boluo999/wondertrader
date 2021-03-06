/*!
 * \file HftMocker.h
 * \project	WonderTrader
 *
 * \author Wesley
 * \date 2020/03/30
 * 
 * \brief 
 */
#pragma once
#include <queue>
#include <fstream>
#include <unordered_map>

#include "HisDataReplayer.h"

#include "../WtCore/IHftStraCtx.h"
#include "../WtCore/HftStrategyDefs.h"

#include "../Share/StdUtils.hpp"
#include "../Share/DLLHelper.hpp"

class HisDataReplayer;

class HftMocker : public IDataSink, public IHftStraCtx
{
public:
	HftMocker(HisDataReplayer* replayer);
	~HftMocker();

public:
	//////////////////////////////////////////////////////////////////////////
	//ITickListener
	virtual void	handle_tick(const char* stdCode, WTSTickData* curTick) override;
	virtual void	handle_bar_close(const char* stdCode, const char* period, uint32_t times, WTSBarStruct* newBar) override;
	virtual void	handle_schedule(uint32_t uDate, uint32_t uTime) override;

	virtual void	handle_init() override;
	virtual void	handle_session_begin() override;
	virtual void	handle_session_end() override;

	//////////////////////////////////////////////////////////////////////////
	//IHftStraCtx
	virtual void on_tick(const char* code, WTSTickData* newTick) override;

	virtual uint32_t id() override;

	virtual void on_init() override;

	virtual bool stra_cancel(uint32_t localid) override;

	virtual OrderIDs stra_cancel(const char* code, bool isBuy, double qty = 0) override;

	virtual OrderIDs stra_buy(const char* stdCode, double price, double qty) override;

	virtual OrderIDs stra_sell(const char* stdCode, double price, double qty) override;

	virtual WTSCommodityInfo* stra_get_comminfo(const char* code) override;

	virtual WTSKlineSlice* stra_get_bars(const char* code, const char* period, uint32_t count) override;

	virtual WTSTickSlice* stra_get_ticks(const char* code, uint32_t count) override;

	virtual WTSTickData* stra_get_last_tick(const char* code) override;

	virtual double stra_get_position(const char* code) override;

	virtual double stra_get_undone(const char* stdCode) override;

	virtual double stra_get_price(const char* code) override;

	virtual uint32_t stra_get_date() override;

	virtual uint32_t stra_get_time() override;

	virtual uint32_t stra_get_secs() override;

	virtual void sub_ticks(const char* code) override;

	virtual void stra_log_text(const char* fmt, ...) override;

public:
	bool	init(WTSVariant* cfg);

private:
	typedef std::function<void()> Task;
	void	postTask(Task task);

	void	procOrder(uint32_t localid);

private:
	HisDataReplayer*	_replayer;

	bool			_use_newpx;
	uint32_t		_error_rate;


	typedef struct _StraFactInfo
	{
		std::string		_module_path;
		DllHandle		_module_inst;
		IHftStrategyFact*	_fact;
		FuncCreateHftStraFact	_creator;
		FuncDeleteHftStraFact	_remover;

		_StraFactInfo()
		{
			_module_inst = NULL;
			_fact = NULL;
		}

		~_StraFactInfo()
		{
			if (_fact)
				_remover(_fact);
		}
	} StraFactInfo;
	StraFactInfo	_factory;

	HftStrategy*	_strategy;

	StdThreadPtr		_thrd;
	StdUniqueMutex		_mtx;
	std::queue<Task>	_tasks;
	bool				_stopped;

	StdRecurMutex		_mtx_control;

	typedef struct _OrderInfo
	{
		bool	_isBuy;
		char	_code[32];
		double	_price;
		double	_total;
		double	_left;
		
		uint32_t	_localid;

		_OrderInfo()
		{
			memset(this, 0, sizeof(_OrderInfo));
		}

	} OrderInfo;
	typedef std::unordered_map<uint32_t, OrderInfo> Orders;
	StdRecurMutex	_mtx_ords;
	Orders			_orders;

	typedef WTSHashMap<std::string> CommodityMap;
	CommodityMap*	_commodities;

	std::unordered_map<std::string, double> _positions;

	std::ofstream	_ofs_signals;
};


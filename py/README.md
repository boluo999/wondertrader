# wt > py
这是wonder trader针对python3适配的子框架<br />
该适配框架仅`适用于CTA策略组合盘的运营`

# 子框架简介
+ common子模块
	> 该模块主要包含了子框架的基本数据结构定义
+ datakit子模块
	> 该模块主要包含了数据落地组件，以及C++底层数据落地的C接口适配模块
+ backtest子模块
	> 该模块主要包含了回测相关的组件，以及C++底层回测的C接口适配模块
+ porter子模块
	> 该模块主要包含了实盘相关的组件，以及C++底层实盘交易的C接口适配模块
+ 其他模块
	> 主要位于根节点下，包含了各个子模块的入口组件
	> - BaseDefs.py	主要定义的Py版本的策略基类，方便用户重写
	> - Context.py	主要定义了用户策略的上下文，可以理解为单策略的运行环境
	> - DataReporter.py	数据报告模块，这个模块后期可能会剥离出来，暂时先放这里
	> - IndexWriter.py	指标输出模块，用于将策略计算的指标数据，输出到指定的地方（数据库、文件等）
	> - ProductMgr.py	品种管理器，主要用于Py环境中的合约属性、品种属性查询
	> - SessionMgr.py	交易时间模板管理器，主要用于Py环境中的交易时段模板管理
	> - WtBtEngine.py	回测引擎转换模块，主要封装底层接口调用
	> - WtDtEngine.py	数据引擎转换模块，主要封装底层接口调用
	> -	WtEngine.py		交易引擎转换模块，主要封装底层接口调用

// 只进行数据交换的文件，且每个model都为单例
#pragma once

class DataModel
{
protected:
	DataModel()
	{

	}
	DataModel(DataModel&) = delete;
};

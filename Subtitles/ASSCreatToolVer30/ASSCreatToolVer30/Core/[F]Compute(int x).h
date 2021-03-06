#include "..\CommenHead.h"

static void Compute(int PosMode)
{
	const short TempStructAmount=StructAmount;
	if(EdgeDistanceX==0)EdgeDistanceX=(short)((ChineseWordWidth*4)/7);
	if(EdgeDistanceY==0)EdgeDistanceY=(short)((ChineseWordWidth*3)/7);


	/*下面计算LineAmount*/
	LineAmount=all[TempStructAmount-1].num_s;//用最后一行的num_s代替总句数

	/*下面计算WordDetail*/
	short Count1=0;
	short Count2=0, Count3=0;
	long Count4=0, Count5=0;
	for(Count1=0;Count1<TempStructAmount;Count1++)//遍历数据结构
	{
		if(all[Count1].num_l==1)//日文
		{
			strcpy_s(WordDetailJP[all[Count1].num_s-1][all[Count1].num_w-1],all[Count1].word);
		}
		else if(all[Count1].num_l==2)//中文
		{
			strcpy_s(WordDetailCN[all[Count1].num_s-1][all[Count1].num_w-1],all[Count1].word);
		}
	}


	/*下面计算计算每句话分割的Part数量*/
	Count1=0;
	for(Count1=1;Count1<TempStructAmount;Count1++)
	{
		if(Count1==TempStructAmount-1)//判断是否为all[]的最后一节
		{
			if(all[Count1].num_l==1)//日文
			{
				AmountJP[all[Count1].num_s-1]=all[Count1].num_w;
			}
			else if(all[Count1].num_l==2)//中文
			{
				AmountCN[all[Count1].num_s-1]=all[Count1].num_w;
			}
		}
		else if((all[Count1-1].num_w!=all[Count1].num_w-1)/*&&(all[Count1-1].num_w!=all[Count1].num_w+1)*/)//判断前后的语言项目是否一致
		{
			if(all[Count1-1].num_l==1)//日文
			{
				AmountJP[all[Count1-1].num_s-1]=all[Count1-1].num_w;
			}
			else if(all[Count1-1].num_l==2)//中文
			{
				AmountCN[all[Count1-1].num_s-1]=all[Count1-1].num_w;
			}
		}
	}


	/*下面计算6种模式的时间*/
	/*
	注：
	0-进入的开始时间;1-进入的结束时间;
	2-强调的开始时间;3-强调的结束时间;
	4-退出的开始时间;5-退出的结束时间;
	*/
	Count2=0, Count3=0;
	Count4=0, Count5=0;
	for(Count2=0;Count2<TempStructAmount;Count2++)//先遍历一次，计算1,2,3,4的参数
	{
		if(all[Count2].num_w==1)//取每句话的第一个字(这里只能计算模式的1,2,3,4项)
		{
			if(all[Count2].num_l==1)//日文
			{
				TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][0]=all[Count2].stime-TimeToEnter-TimeToStart;
				TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][1]=TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][0]+TimeToEnter;
				TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][2]=all[Count2].stime;
				TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][3]=all[Count2].etime;
			}
			else if(all[Count2].num_l==2)//中文
			{
				TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][0]=all[Count2].stime-TimeToEnter-TimeToStart;
				TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][1]=TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][0]+TimeToEnter;
				Count5=(all[Count2].etime-all[Count2].stime)/(AmountCN[all[Count2].num_s-1]+1);//+1的平均值
				TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][2]=all[Count2].stime+Count5*(all[Count2].num_w-1);
				TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][3]=TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][2]+Count5;
			}
		}
		else//这里表示的不是每句话的第一个字
		{
			if(all[Count2].num_l==1)//日文
			{
				TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][0]=TimeJP[all[Count2].num_s-1][0][0]+AppearanceAlternation*(all[Count2].num_w-1);
				TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][1]=TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][0]+TimeToEnter;
				TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][2]=all[Count2].stime;
				TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][3]=all[Count2].etime;
			}
			else if(all[Count2].num_l==2)//中文
			{
				TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][0]=TimeCN[all[Count2].num_s-1][0][0]+AppearanceAlternation*(all[Count2].num_w-1);
				TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][1]=TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][0]+TimeToEnter;
				Count5=(all[Count2].etime-all[Count2].stime)/(AmountCN[all[Count2].num_s-1]+1);//+1的平均值
				TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][2]=all[Count2].stime+Count5*(all[Count2].num_w-1);
				TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][3]=TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][2]+Count5;
			}
		}
	}
	for(Count2=0;Count2<TempStructAmount;Count2++)//第二次遍历，计算4,5的参数
	{
		if(all[Count2].num_l==1)//日文
		{
			if(all[Count2].num_w==AmountJP[all[Count2].num_s-1])//取每句日文的最后一个字
			{
				if(all[Count2].num_s==LineAmount)//取最后一句话的最后一个字
				{
					for(Count3=0;Count3<AmountJP[all[Count2].num_s-1];Count3++)
					{
						TimeJP[all[Count2].num_s-1][Count3][4]=TimeJP[all[Count2].num_s-1][AmountJP[all[Count2].num_s-1]-1][3]+TimeToLeave+AppearanceAlternation*Count3;
						TimeJP[all[Count2].num_s-1][Count3][5]=TimeJP[all[Count2].num_s-1][Count3][4]+TimeToDisappear;
					}
				}
				else//不是最后一句日文的最后一个字
				{
					Count4=TimeJP[all[Count2].num_s-1][all[Count2].num_w-1][3]+TimeToLeave;
					Count5=TimeJP[all[Count2].num_s][0][0];
					if(Count4>Count5)//如果前一句的最后一个字的退出时间大于后一个句的第一个字(判断)
					{
						for(Count3=0;Count3<AmountJP[all[Count2].num_s-1];Count3++)
						{
							TimeJP[all[Count2].num_s-1][Count3][4]=TimeJP[all[Count2].num_s][0][0]-TimeToLeave+AppearanceAlternation*Count3;
							TimeJP[all[Count2].num_s-1][Count3][5]=TimeJP[all[Count2].num_s-1][Count3][4]+TimeToDisappear;
						}
					}
					else//反之，不判断
					{
						for(Count3=0;Count3<AmountJP[all[Count2].num_s-1];Count3++)
						{
							TimeJP[all[Count2].num_s-1][Count3][4]=TimeJP[all[Count2].num_s-1][AmountJP[all[Count2].num_s-1]-1][3]+TimeToLeave+AppearanceAlternation*Count3;
							TimeJP[all[Count2].num_s-1][Count3][5]=TimeJP[all[Count2].num_s-1][Count3][4]+TimeToDisappear;
						}
					}
				}
			}
		}
		else if(all[Count2].num_l==2)//中文
		{
			if(all[Count2].num_w==AmountCN[all[Count2].num_s-1])//取每句中文的最后一个字
			{
				if(all[Count2].num_s==LineAmount)//取最后一句话的最后一个字
				{
					for(Count3=0;Count3<AmountCN[all[Count2].num_s-1];Count3++)
					{
						TimeCN[all[Count2].num_s-1][Count3][4]=TimeCN[all[Count2].num_s-1][AmountCN[all[Count2].num_s-1]-1][3]+TimeToLeave+AppearanceAlternation*Count3;
						TimeCN[all[Count2].num_s-1][Count3][5]=TimeCN[all[Count2].num_s-1][Count3][4]+TimeToDisappear;
					}
				}
				else//不是最后一句日文的最后一个字
				{
					Count4=TimeCN[all[Count2].num_s-1][all[Count2].num_w-1][3]+TimeToLeave;
					Count5=TimeCN[all[Count2].num_s][0][0];
					if(Count4>Count5)//如果前一句的最后一个字的退出时间大于后一个句的第一个字(判断)
					{
						for(Count3=0;Count3<AmountCN[all[Count2].num_s-1];Count3++)
						{
							TimeCN[all[Count2].num_s-1][Count3][4]=TimeCN[all[Count2].num_s][0][0]-TimeToLeave+AppearanceAlternation*Count3;
							TimeCN[all[Count2].num_s-1][Count3][5]=TimeCN[all[Count2].num_s-1][Count3][4]+TimeToDisappear;
						}
					}
					else//反之，不判断
					{
						for(Count3=0;Count3<AmountCN[all[Count2].num_s-1];Count3++)
						{
							TimeCN[all[Count2].num_s-1][Count3][4]=TimeCN[all[Count2].num_s-1][AmountCN[all[Count2].num_s-1]-1][3]+TimeToLeave+AppearanceAlternation*Count3;
							TimeCN[all[Count2].num_s-1][Count3][5]=TimeCN[all[Count2].num_s-1][Count3][4]+TimeToDisappear;
						}
					}
				}
			}
		}
	}


	/*<下面计算每个字的像素长度*/
	Count1=0, Count2=0, Count3=0;
	Count4=0, Count5=0;
	short Count6=0, Count7=0, Count8=0;
	short Count9=0, Count0=0;
	for(Count1=0;Count1<TempStructAmount;Count1++)//遍历数据结构
	{
		Count8=0;//记录长度的临时变量
		Count5=strlen(all[Count1].word);//存储第Count1行的数据结构的字长度
		Count9=-1,Count0=-1;
		for(Count2=0;Count2<Count5;Count2++)//对字的长度进行循环
		{
			Count4=(long)((int)all[Count1].word[Count2]);//存储第Count2个字符的ASCII码
			if((Count4<=126&&Count4>=32))//P.S.如果不是a~z或A~Z,就以a的长度为其长度
			{
				if((Count9-Count0)==1)
				{
					Count8+=(ChineseWordWidth/2);
					Count0=Count2;
					continue;
				}
				Count0=Count2;//记录最后一次进这
				Count6=(short)Count4-asc1;
				Count7=(short)Count4-asc2;
				if(Count6<26&&Count6>=0)//大写判断
				{
					Count8+=EnglishWordWidthB[Count6];
				}
				else if(Count7<26&&Count7>=0)//小写判断
				{
					Count8+=EnglishWordWidthL[Count6];
				}
				else//非大小写的英文字符
				{
					Count8+=EnglishWordWidthL[0];
				}
			}
			else//非英文字符
			{
				Count8+=(ChineseWordWidth/2);
				Count9=Count2;//记录最后一次进这
			}
		}
		if(all[Count1].num_l==1)//日文
		{
			WordLenthJP[all[Count1].num_s-1][all[Count1].num_w-1]=Count8;
		}
		else if(all[Count1].num_l==2)//中文
		{
			WordLenthCN[all[Count1].num_s-1][all[Count1].num_w-1]=Count8;
		}
	}


	/*<下面计算每句话的像素长度*/
	Count1=0, Count2=0, Count3=0;
	Count4=0, Count5=0;
	Count6=0, Count7=0, Count8=0;
	for(Count1=0;Count1<LineAmount;Count1++)
	{
		Count8=0;
		for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
		{
			Count8+=WordLenthJP[Count1][Count2];
		}
		LineLenthJP[Count1]=Count8;
		Count8=0;
		for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
		{
			Count8+=WordLenthCN[Count1][Count2];
		}
		LineLenthCN[Count1]=Count8;
	}


	/*下面计算每个字的位置 (对齐方式\an5)*/
	/*
	pos计算分4类：(数字是PosMode的取值)
	11-日文左下,中文右上;12-日文右下,中文左上;13-日文中文都居中;14-日文从左下到右下混排,中文从右上到左上混排;
	21-日文左上,中文右下;22-日文右上,中文左下;23-日文中文都居中;24-日文从左上到右上混排,中文从右下到左下混排;
	31-(竖式)日文左上,中文右下;32-(竖式)居中;
	41-(竖式)日文右下,中文左上;42-(竖式)居中;
	*/
	Count1=0, Count2=0, Count3=0;//(short)
	Count4=0, Count5=0;//(long)
	Count6=0, Count7=0, Count8=0;//(short)
	if(PosMode==11)//11-日文左下,中文右上
	{
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			Count8=EdgeDistanceX;//宽
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthJP[Count1][Count2]/2;
					PosJP[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthJP[Count1][Count2-1]/2)+(WordLenthJP[Count1][Count2]/2);
					PosJP[Count1][Count2][0]=Count8;
				}
				PosJP[Count1][Count2][1]=Height-(ChineseWordWidth/2)-EdgeDistanceY;
			}
			Count8=Width-EdgeDistanceX-LineLenthCN[Count1];//宽
			for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthCN[Count1][Count2]/2;
					PosCN[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthCN[Count1][Count2-1]/2)+(WordLenthCN[Count1][Count2]/2);
					PosCN[Count1][Count2][0]=Count8;
				}
				PosCN[Count1][Count2][1]=EdgeDistanceY+(ChineseWordWidth/2);
			}
		}
	}
	else if(PosMode==12)//12-日文右下,中文左上
	{
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			Count8=Width-EdgeDistanceX-LineLenthJP[Count1];//宽
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthJP[Count1][Count2]/2;
					PosJP[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthJP[Count1][Count2-1]/2)+(WordLenthJP[Count1][Count2]/2);
					PosJP[Count1][Count2][0]=Count8;
				}
				PosJP[Count1][Count2][1]=Height-(ChineseWordWidth/2)-EdgeDistanceY;
			}
			Count8=EdgeDistanceX;//宽
			for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthCN[Count1][Count2]/2;
					PosCN[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthCN[Count1][Count2-1]/2)+(WordLenthCN[Count1][Count2]/2);
					PosCN[Count1][Count2][0]=Count8;
				}
				PosCN[Count1][Count2][1]=EdgeDistanceY+(ChineseWordWidth/2);
			}
		}
	}
	else if(PosMode==13)//13-日文下,中文上,居中
	{
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			Count8=(Width/2)-(LineLenthJP[Count1]/2);
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthJP[Count1][Count2]/2;
					PosJP[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthJP[Count1][Count2-1]/2)+(WordLenthJP[Count1][Count2]/2);
					PosJP[Count1][Count2][0]=Count8;
				}
				PosJP[Count1][Count2][1]=Height-(ChineseWordWidth/2)-EdgeDistanceY;
			}
			Count8=(Width/2)-(LineLenthCN[Count1]/2);
			for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthCN[Count1][Count2]/2;
					PosCN[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthCN[Count1][Count2-1]/2)+(WordLenthCN[Count1][Count2]/2);
					PosCN[Count1][Count2][0]=Count8;
				}
				PosCN[Count1][Count2][1]=EdgeDistanceY+(ChineseWordWidth/2);
			}
		}
	}
	/*else if(PosMode==14)//14-日文从左下到右下混排,中文从右上到左上混排
	{
	}*/
	else if(PosMode==21)//21-日文左上,中文右下
	{
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			Count8=EdgeDistanceX;//宽
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthJP[Count1][Count2]/2;
					PosJP[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthJP[Count1][Count2-1]/2)+(WordLenthJP[Count1][Count2]/2);
					PosJP[Count1][Count2][0]=Count8;
				}
				PosJP[Count1][Count2][1]=(ChineseWordWidth/2)+EdgeDistanceY;
			}
			Count8=Width-EdgeDistanceX-LineLenthCN[Count1];//宽
			for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthCN[Count1][Count2]/2;
					PosCN[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthCN[Count1][Count2-1]/2)+(WordLenthCN[Count1][Count2]/2);
					PosCN[Count1][Count2][0]=Count8;
				}
				PosCN[Count1][Count2][1]=Height-(ChineseWordWidth/2)-EdgeDistanceY;
			}
		}
	}
	else if(PosMode==22)//22-日文右上,中文左下
	{
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			Count8=Width-EdgeDistanceX-LineLenthJP[Count1];//宽
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthJP[Count1][Count2]/2;
					PosJP[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthJP[Count1][Count2-1]/2)+(WordLenthJP[Count1][Count2]/2);
					PosJP[Count1][Count2][0]=Count8;
				}
				PosJP[Count1][Count2][1]=(ChineseWordWidth/2)+EdgeDistanceY;
			}
			Count8=EdgeDistanceX;//宽
			for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthCN[Count1][Count2]/2;
					PosCN[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthCN[Count1][Count2-1]/2)+(WordLenthCN[Count1][Count2]/2);
					PosCN[Count1][Count2][0]=Count8;
				}
				PosCN[Count1][Count2][1]=Height-(ChineseWordWidth/2)-EdgeDistanceY;
			}
		}
	}
	else if(PosMode==23)//23-日文上,中文下,居中
	{
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			Count8=(Width/2)-(LineLenthJP[Count1]/2);
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthJP[Count1][Count2]/2;
					PosJP[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthJP[Count1][Count2-1]/2)+(WordLenthJP[Count1][Count2]/2);
					PosJP[Count1][Count2][0]=Count8;
				}
				PosJP[Count1][Count2][1]=(ChineseWordWidth/2)+EdgeDistanceY;
			}
			Count8=(Width/2)-(LineLenthCN[Count1]/2);
			for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthCN[Count1][Count2]/2;
					PosCN[Count1][Count2][0]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthCN[Count1][Count2-1]/2)+(WordLenthCN[Count1][Count2]/2);
					PosCN[Count1][Count2][0]=Count8;
				}
				PosCN[Count1][Count2][1]=Height-(ChineseWordWidth/2)-EdgeDistanceY;
			}
		}
	}
	/*else if(PosMode==24)//24-日文从左上到右上混排,中文从右下到左下混排
	{
	}*/
	else if(PosMode==31)//31-(竖式)日文左上,中文右下
	{
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			Count8=EdgeDistanceX;//高度
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthJP[Count1][Count2]/2;
					PosJP[Count1][Count2][1]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthJP[Count1][Count2-1]/2)+(WordLenthJP[Count1][Count2]/2);
					PosJP[Count1][Count2][1]=Count8;
				}
				PosJP[Count1][Count2][0]=(ChineseWordWidth/2)+EdgeDistanceY;
			}
			Count8=Height-EdgeDistanceX-(LineLenthCN[Count1]);//高度
			for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
			{
				if(Count2==0)
				{
					Count8+=WordLenthCN[Count1][Count2]/2;
					PosCN[Count1][Count2][1]=Count8;
				}
				else
				{
					Count8+=(WordLenthCN[Count1][Count2-1]/2)+(WordLenthCN[Count1][Count2]/2);
					PosCN[Count1][Count2][1]=Count8;
				}
				PosCN[Count1][Count2][0]=Height-(ChineseWordWidth/2)-EdgeDistanceY;
			}
		}
	}
	else if(PosMode==32)//32-(竖式)日文左,中文右,居中
	{
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			Count8=(Height/2)-(LineLenthJP[Count1]/2);//高度
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthJP[Count1][Count2]/2;
					PosJP[Count1][Count2][1]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthJP[Count1][Count2-1]/2)+(WordLenthJP[Count1][Count2]/2);
					PosJP[Count1][Count2][1]=Count8;
				}
				PosJP[Count1][Count2][0]=(ChineseWordWidth/2)+EdgeDistanceY;
			}
			Count8=(Height/2)-(LineLenthCN[Count1]/2);//高度
			for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
			{
				if(Count2==0)
				{
					Count8+=WordLenthCN[Count1][Count2]/2;
					PosCN[Count1][Count2][1]=Count8;
				}
				else
				{
					Count8+=(WordLenthCN[Count1][Count2-1]/2)+(WordLenthCN[Count1][Count2]/2);
					PosCN[Count1][Count2][1]=Count8;
				}
				PosCN[Count1][Count2][0]=Height-(ChineseWordWidth/2)-EdgeDistanceY;
			}
		}
	}
	else if(PosMode==41)//41-(竖式)日文右下,中文左上
	{
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			Count8=Height-EdgeDistanceX-(LineLenthJP[Count1]);//高度
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthJP[Count1][Count2]/2;
					PosJP[Count1][Count2][1]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthJP[Count1][Count2-1]/2)+(WordLenthJP[Count1][Count2]/2);
					PosJP[Count1][Count2][1]=Count8;
				}
				PosJP[Count1][Count2][0]=Height-(ChineseWordWidth/2)-EdgeDistanceY;
			}
			Count8=EdgeDistanceX;//高度
			for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
			{
				if(Count2==0)
				{
					Count8+=WordLenthCN[Count1][Count2]/2;
					PosCN[Count1][Count2][1]=Count8;
				}
				else
				{
					Count8+=(WordLenthCN[Count1][Count2-1]/2)+(WordLenthCN[Count1][Count2]/2);
					PosCN[Count1][Count2][1]=Count8;
				}
				PosCN[Count1][Count2][0]=(ChineseWordWidth/2)+EdgeDistanceY;
			}
		}
	}
	else if(PosMode==42)//42-(竖式)日文右,中文左,居中
	{
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			Count8=(Height/2)-(LineLenthJP[Count1]/2);//高度
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//日文
			{
				if(Count2==0)//本行第一个字
				{
					Count8+=WordLenthJP[Count1][Count2]/2;
					PosJP[Count1][Count2][1]=Count8;
				}
				else//不是本行第一个字
				{
					Count8+=(WordLenthJP[Count1][Count2-1]/2)+(WordLenthJP[Count1][Count2]/2);
					PosJP[Count1][Count2][1]=Count8;
				}
				PosJP[Count1][Count2][0]=Height-(ChineseWordWidth/2)-EdgeDistanceY;
			}
			Count8=(Height/2)-(LineLenthCN[Count1]/2);//高度
			for(Count2=0;Count2<AmountCN[Count1];Count2++)//中文
			{
				if(Count2==0)
				{
					Count8+=WordLenthCN[Count1][Count2]/2;
					PosCN[Count1][Count2][1]=Count8;
				}
				else
				{
					Count8+=(WordLenthCN[Count1][Count2-1]/2)+(WordLenthCN[Count1][Count2]/2);
					PosCN[Count1][Count2][1]=Count8;
				}
				PosCN[Count1][Count2][0]=(ChineseWordWidth/2)+EdgeDistanceY;
			}
		}
	}
	else
	{
		ass_temp<<"Error in value: PosMode!~"<<endl;
	}








		/*Test*/
		ass_temp<<endl;
		ass_temp<<"LineAmount:"<<endl;
		ass_temp<<LineAmount<<endl;
		ass_temp<<endl;
		ass_temp<<endl;
		ass_temp<<"WordDetailJP"<<endl;
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			for(Count2=0;Count2<AmountJP[Count1];Count2++)//JP
			{
				ass_temp<<"WordDetailJP["<<Count1<<"]["<<Count2<<"]="<<WordDetailJP[Count1][Count2]<<endl;
			}
			if(FileMode==1||FileMode==3||FileMode==5||FileMode==7)
			{
				for(Count2=0;Count2<AmountCN[Count1];Count2++)//CN
				{
					ass_temp<<"WordDetailCN["<<Count1<<"]["<<Count2<<"]="<<WordDetailCN[Count1][Count2]<<endl;
				}
			}
		}
		ass_temp<<endl;
		ass_temp<<endl;
		ass_temp<<"AmountJP:"<<endl;
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			ass_temp<<"AmountJP["<<Count1<<"]="<<AmountJP[Count1]<<endl;
		}
		if(FileMode==1||FileMode==3||FileMode==5||FileMode==7)
		{
			ass_temp<<endl;
			ass_temp<<endl;
			ass_temp<<"AmountCN:"<<endl;
			for(Count1=0;Count1<LineAmount;Count1++)
			{
				ass_temp<<"AmountCN["<<Count1<<"]="<<AmountCN[Count1]<<endl;
			}
		}
		ass_temp<<endl;
		ass_temp<<endl;
		ass_temp<<"TimeJP:"<<endl;
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			for(Count2=0;Count2<AmountJP[Count1];Count2++)
			{
				ass_temp<<"TimeJP["<<Count1<<"]["<<Count2<<"][0]="<<itc(TimeJP[Count1][Count2][0])<<endl;
				ass_temp<<"TimeJP["<<Count1<<"]["<<Count2<<"][1]="<<itc(TimeJP[Count1][Count2][1])<<endl;
				ass_temp<<"TimeJP["<<Count1<<"]["<<Count2<<"][2]="<<itc(TimeJP[Count1][Count2][2])<<endl;
				ass_temp<<"TimeJP["<<Count1<<"]["<<Count2<<"][3]="<<itc(TimeJP[Count1][Count2][3])<<endl;
				ass_temp<<"TimeJP["<<Count1<<"]["<<Count2<<"][4]="<<itc(TimeJP[Count1][Count2][4])<<endl;
				ass_temp<<"TimeJP["<<Count1<<"]["<<Count2<<"][5]="<<itc(TimeJP[Count1][Count2][5])<<endl;
				ass_temp<<endl;
			}
		}
		ass_temp<<endl;
		ass_temp<<endl;	
		if(FileMode==1||FileMode==3||FileMode==5||FileMode==7)
		{
			ass_temp<<"TimeCN:"<<endl;
			for(Count1=0;Count1<LineAmount;Count1++)
			{
				for(Count2=0;Count2<AmountCN[Count1];Count2++)
				{
					ass_temp<<"TimeCN["<<Count1<<"]["<<Count2<<"][0]="<<itc(TimeCN[Count1][Count2][0])<<endl;
					ass_temp<<"TimeCN["<<Count1<<"]["<<Count2<<"][1]="<<itc(TimeCN[Count1][Count2][1])<<endl;
					ass_temp<<"TimeCN["<<Count1<<"]["<<Count2<<"][2]="<<itc(TimeCN[Count1][Count2][2])<<endl;
					ass_temp<<"TimeCN["<<Count1<<"]["<<Count2<<"][3]="<<itc(TimeCN[Count1][Count2][3])<<endl;
					ass_temp<<"TimeCN["<<Count1<<"]["<<Count2<<"][4]="<<itc(TimeCN[Count1][Count2][4])<<endl;
					ass_temp<<"TimeCN["<<Count1<<"]["<<Count2<<"][5]="<<itc(TimeCN[Count1][Count2][5])<<endl;
					ass_temp<<endl;
				}
			}
		}
		ass_temp<<endl;
		ass_temp<<endl;
		ass_temp<<"LineLenthJP:"<<endl;
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			ass_temp<<"LineLenthJP["<<Count1<<"]="<<LineLenthJP[Count1]<<endl;
		}
		if(FileMode==1||FileMode==3||FileMode==5||FileMode==7)
		{
			ass_temp<<endl;
			ass_temp<<endl;
			ass_temp<<"LineLenthCN:"<<endl;
			for(Count1=0;Count1<LineAmount;Count1++)
			{
				ass_temp<<"LineLenthCN["<<Count1<<"]="<<LineLenthCN[Count1]<<endl;
			}
		}
		system("PAUSE");
		ass_temp<<endl;
		ass_temp<<endl;
		ass_temp<<"WordLenthJP"<<endl;
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			for(Count2=0;Count2<AmountJP[Count1];Count2++)
			{
				ass_temp<<"WordLenthJP["<<Count1<<"]["<<Count2<<"]="<<WordLenthJP[Count1][Count2]<<endl;
			}
		}
		ass_temp<<endl;
		ass_temp<<endl;
		if(FileMode==1||FileMode==3||FileMode==5||FileMode==7)
		{
			ass_temp<<"WordLenthCN"<<endl;
			for(Count1=0;Count1<LineAmount;Count1++)
			{
				for(Count2=0;Count2<AmountCN[Count1];Count2++)
				{
					ass_temp<<"WordLenthCN["<<Count1<<"]["<<Count2<<"]="<<WordLenthCN[Count1][Count2]<<endl;
				}
			}
		}
		system("PAUSE");
		ass_temp<<endl;
		ass_temp<<endl;
		ass_temp<<"PosJP"<<endl;
		for(Count1=0;Count1<LineAmount;Count1++)
		{
			for(Count2=0;Count2<AmountJP[Count1];Count2++)
			{
				ass_temp<<"PosJP["<<Count1<<"]["<<Count2<<"][0]="<<PosJP[Count1][Count2][0]<<endl;
				ass_temp<<"PosJP["<<Count1<<"]["<<Count2<<"][1]="<<PosJP[Count1][Count2][1]<<endl;
			}
			ass_temp<<endl;
		}
		ass_temp<<endl;
		ass_temp<<endl;
		if(FileMode==1||FileMode==3||FileMode==5||FileMode==7)
		{
		ass_temp<<"PosCN"<<endl;
		for(Count1=0;Count1<LineAmount;Count1++)
		{
				for(Count2=0;Count2<AmountCN[Count1];Count2++)
				{
					ass_temp<<"PosCN["<<Count1<<"]["<<Count2<<"][0]="<<PosCN[Count1][Count2][0]<<endl;
					ass_temp<<"PosCN["<<Count1<<"]["<<Count2<<"][1]="<<PosCN[Count1][Count2][1]<<endl;
				}
				ass_temp<<endl;
			}
		}
}
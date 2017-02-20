
/*
define const values
*/

// 定义窗口常量
#define WINDOW_CAPTION		"Snake"			// 窗口标题
#define WINDOW_WIDTH		912				// 窗口宽度
#define WINDOW_HEIGHT		816				// 窗口高度

// 定义得分、级别、每关所需得分、当前游戏块下落的速度等位置
#define SCORE_POSITION_X	(612+60)		// 绘制得分位置
#define SCORE_POSITION_Y	(65+180)

// 定义纹理数据类型
#define NORMAL_BALL			0				// 普通小球(被吃蛇身会变长一格)
#define HARM_BALL			1				// 伤害小球(被吃蛇身会减少一格)
#define GOOD_BALL			2				// 物品小球(被吃会出现物品道具)
#define HEAD				3				// 蛇头
#define TAIL				4				// 蛇尾
// 定义物品纹理数据类型
#define FOOD				5				// 物品道具(被吃蛇身会增加两格，分数加倍)

#define TEXTURE_COUNTS		6				// 纹理数据总数

// 定义纹理中心点到边的距离
#define	RADIUS				12

// 定义每行每列有多少个Square
#define PER_ROW				38
#define PER_COL				34

// 定义蛇移动的间隔
#define TIME_INTERVAL		12
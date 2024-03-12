#include <stdio.h>
#include <string.h>
//定义无穷大为int上限的一半，防止计算溢出
#define INF 0x3f3f3f3f

int vertexCount; //顶点数
int edgeTime[1000][1000], // edgeTime[i][j]表示顶点i和j之间的时间, 
	edgeLength[1000][1000]; // edgeLength[i][j]表示顶点i和j之间的距离
int optimalTime[1000], // optimalTime[i]表示从起点到i的最佳时间
	optimalDist[1000]; // optimalDist[i]表示从起点到i的最佳距离
int isVisit[1000], // isVisit[i]表示顶点i是否已经确定了最短路径
	preVertex[1000], // preVertex[i]表示从起点到i的最短路径中,i的前一个顶点
	finalPath[1000]; // finalPath[]存储最佳路径

void dijkstra() {
	while (1) {
		// 每次循环都选出一个尚未确定最佳时间且当前记录最佳时间最小的顶点
		// minTemp为当前找到的最佳时间，初始化为INF；minVertex为当前找到的最佳时间所对应的顶点下标，初始化为-1
		int minTime = INF, minVertex = -1;
		for (int i = 1; i < vertexCount + 1; i++) {
			if (isVisit[i] != 1 && optimalTime[i] < minTime) {
				// 如果找到更小的最佳时间，则更新minTemp和minVertexTemp
				minTime = optimalTime[i];
				minVertex = i;
			}
		}
		// 如果没有找到minVertex，说明所有连通的顶点都已经确定最佳时间了，结束循环
		if (minVertex == -1) {
			break;
		}
		// 将minVertex的最佳时间确定
		isVisit[minVertex] = 1;

		// 更新optimalTime和optimalDist
		for (int i = 1; i < vertexCount + 1; i++) {
			// 如果该边已经确定过最佳时间或该边不存在，则跳过
			if (isVisit[i] || !edgeTime[minVertex][i]) {
				continue;
			}
			// 如果找到一条time更小的路径，则更新对应顶点的optimalTime
			if (optimalTime[i] > optimalTime[minVertex] + edgeTime[minVertex][i]) {
				optimalTime[i] = optimalTime[minVertex] + edgeTime[minVertex][i];
				optimalDist[i] = optimalDist[minVertex] + edgeLength[minVertex][i];
				preVertex[i] = minVertex;
			}
			// 特别地，如果两条路径的time相同，则选择dist更短的那条
			else if (optimalTime[i] == optimalTime[minVertex] + edgeTime[minVertex][i]) {
				if (optimalDist[i] > optimalDist[minVertex] + edgeLength[minVertex][i]) {
					optimalDist[i] = optimalDist[minVertex] + edgeLength[minVertex][i];
					preVertex[i] = minVertex;
				}
			}
		}
	}
}

int main() {
	int EdgeCount, destVertex; // 边数，终点下标
	scanf_s("%d%d%d", &vertexCount, &EdgeCount, &destVertex);
	// 建立图的edgeTime和edgeLength数组
	while (EdgeCount--) {
		int v1, v2, time, length;
		scanf_s("%d%d%d%d", &v1, &v2, &time, &length);
		edgeTime[v1][v2] = edgeTime[v2][v1] = time;
		edgeLength[v1][v2] = edgeLength[v2][v1] = length;
	}
	// 初始化optimalTime、optimalDist、preVertex数组
	memset(optimalTime, INF, sizeof(optimalTime));
	memset(optimalDist, INF, sizeof(optimalDist));
	memset(preVertex, -1, sizeof(preVertex));
	// 直接将起点到起点的最佳时间和最佳距离设为0
	optimalTime[1] = 0;
	optimalDist[1] = 0;
	// 调用dijkstra函数，找到最佳时间和最佳距离
	dijkstra();
	// 打印最佳时间和最佳距离
	printf("%d %d ", optimalTime[destVertex], optimalDist[destVertex]);
	// 将最佳路径存储到finalPath中
	int k = 1;
	finalPath[0] = destVertex;
	while (preVertex[destVertex] != -1) {
		destVertex = preVertex[destVertex];
		finalPath[k++] = destVertex;
	}
	// 打印最佳路径，注意要逆向遍历finalPath
	for (int i = k - 1; i >= 1; i--) {
		printf("%d->", finalPath[i]);
	}
	printf("%d\n", finalPath[0]);
	return 0;
}
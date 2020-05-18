#include<vector>
#include<math.h>
#include<stdlib.h>
using namespace std;

class KMeans
{
private:	
	int K;
	int rows;
	vector<float> *centroids;
	vector<int>pred;

public:
	KMeans()
	{
		K = 0;
		rows = 0;
		centroids = new vector<float>[K];
	}
	KMeans(int K)
	{
		this->K = K;
		rows = 0;
		centroids = new vector<float>[K];
	}
	void initialize(vector<float>image[])
	{
		srand(time(0));

		for(int i=0;i<K;i++)
		{
			int select = rand()%rows;
			centroids[i] = image[select];
		}
	}
	float distance(vector<float> v1,vector<float> v2)
	{
		float dist;
		for(int i=0;i<v1.size();i++)
			dist = dist + pow((v1[i] - v2[i]),2);
		dist = sqrt(dist);
		return dist;	
	}
	vector<float> Mean(vector<vector<float>> v,vector<float>image[])
	{
		vector<float> m;
		if(v.size() == 0)
		{
			srand(time(0));
			m = image[rand()%rows];
		}
		else
		{
			for(int i=0;i<v[0].size();i++)
			{
				float sum = 0;
				for(int j=0;j<v.size();j++)
					sum = sum + v[j][i];
				m.push_back(sum/v.size());
			}
		}
		return m;		
	}
	void fit(vector<float>image[],int rows,int iterations = 10)
	{
		this->rows = rows;
		initialize(image);
		while(iterations--)
		{
			vector<vector<float>>cluster[K];
			for(int i=0;i<rows;i++)
			{
				float Min = 1000.0;
				int centroid_no = -1;
				for(int j=0;j<K;j++)
				{
					if(distance(image[i],centroids[j]) < Min)
					{
						Min = distance(image[i],centroids[j]);
						centroid_no = j;
					}		
				}
				cluster[centroid_no].push_back(image[i]);
			}
			for(int i=0;i<K;i++)
			{
				centroids[i] = Mean(cluster[i],image);
			}
		}
	}
	void predict(vector<float>image[])
	{
		for(int j=0;j<rows;j++)
		{
			int val = -1;
			float Min = 10000000.0;
			for(int i=0;i<K;i++)
			{
				if(distance(image[j],centroids[i]) < Min)
				{
					Min = distance(image[j],centroids[i]);
					val = i;
				}
			}
			pred.push_back(val);
		}
	}
	vector<float> *getCentroids()
	{
		return centroids;
	}
	vector<int> getPredictions()
	{
		return pred;
	}
	vector<float> getCentroid(int index)
	{
		int actual_index = pred.at(index);
		return centroids[actual_index];
	}

};

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
typedef struct kVector
{
    long double *kv=new long double[1025];
} kVector;
typedef struct tVector
{
    long double *tv=new long double[1025];
} tVector;
long double sum,SUM,cost,tmp,LSV[5]={422.58,319.3984375,319.234,319.624};
kVector rData,Layer_1,Layer_2,Layer_3,b1LPDs,b1Layer,b2LPDs,b2Layer,b3LPDs,b3Layer,*w0LPDs=new kVector[1025],*w0Layer=new kVector[1025],*w1LPDs=new kVector[1025],*w1Layer=new kVector[1025],*w2LPDs=new kVector[1025],*w2Layer=new kVector[1025],*w3LPDs=new kVector[1025],*w3Layer=new kVector[11],*costPDLs=new kVector[5],*originalWS=new kVector[4];
tVector rExpected,b4LPDs,b4Layer,Layer_4;
void getParameters();
void updateData();
void runModel();
void computePDs();
void clearPDA();
void getData(std::string data,std::string expected);
inline long double sigmoid(long double v,long double t);
inline long double dSigmoid(long double v,long double t);
int main(int argc,char **argv)
{
    if(argc<2) return 0;
    clearPDA();
    getParameters();
    for(int i=0;i<10;++i)
    {
        getData("TrainingData/"+std::string(argv[1])+"/"+char(i+48)+".mld","TrainingData/"+std::string(argv[1])+"/"+char(i+48)+".exp.mld");
        runModel();
        computePDs();
    }
    /*for(int i=0;i<10;++i)
    {
        std::cout<<"Number "<<i<<":"<<Layer_4.tv[i]<<std::endl;
    }
    sum=0;
    for(int i=0;i<10;++i)
    {
        sum+=(rExpected.tv[i]-Layer_4.tv[i])*(rExpected.tv[i]-Layer_4.tv[i]);
    }
    std::cout<<"cost:"<<sum<<std::endl;
    cost=sum;*/
    system("pause");
}
inline long double sigmoid(long double v,long double t)
{
    return 1/(1+exp(-v/t));
}
inline long double dSigmoid(long double v,long double t)
{
    return (sigmoid(v,t)*(1-sigmoid(v,t)))/t;
}
void computePDs()
{
    for(int i=0;i<10;++i)
        costPDLs[4].kv[i]=2*(Layer_4.tv[i]-rExpected.tv[i]);
    for(int i=0;i<10;++i)
    {
        for(int j=0;j<1024;++j)
        {
            w3LPDs[i].kv[j]+=Layer_3.kv[j]*dSigmoid(originalWS[3].kv[i],LSV[3])*costPDLs[4].kv[i];
        }
    }
    for(int i=0;i<10;++i)
    {
        b4LPDs.tv[i]+=dSigmoid(originalWS[3].kv[i],LSV[3])*costPDLs[4].kv[i];
    }
    for(int j=0;j<1024;++j)
    {
        sum=0;
        for(int i=0;i<10;++i)
        {
            sum+=w3Layer[i].kv[j]*dSigmoid(originalWS[3].kv[i],LSV[3])*costPDLs[4].kv[i];
        }
        costPDLs[3].kv[j]=sum;
    }
    //
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            w2LPDs[i].kv[j]+=Layer_2.kv[j]*dSigmoid(originalWS[2].kv[i],LSV[2])*costPDLs[3].kv[i];
        }
    }
    for(int i=0;i<1024;++i)
    {
        b3LPDs.kv[i]+=dSigmoid(originalWS[2].kv[i],LSV[2])*costPDLs[3].kv[i];
    }
    for(int j=0;j<1024;++j)
    {
        sum=0;
        for(int i=0;i<1024;++i)
        {
            sum+=w2Layer[i].kv[j]*dSigmoid(originalWS[2].kv[i],LSV[2])*costPDLs[3].kv[i];
        }
        costPDLs[2].kv[j]=sum;
    }
    //2
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            w1LPDs[i].kv[j]+=Layer_1.kv[j]*dSigmoid(originalWS[1].kv[i],LSV[1])*costPDLs[2].kv[i];
        }
    }
    for(int i=0;i<1024;++i)
    {
        b2LPDs.kv[i]+=dSigmoid(originalWS[1].kv[i],LSV[1])*costPDLs[2].kv[i];
    }
    for(int j=0;j<1024;++j)
    {
        sum=0;
        for(int i=0;i<1024;++i)
        {
            sum+=w1Layer[i].kv[j]*dSigmoid(originalWS[1].kv[i],LSV[1])*costPDLs[2].kv[i];
        }
        costPDLs[1].kv[j]=sum;
    }
    //1
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            w0LPDs[i].kv[j]+=rData.kv[j]*dSigmoid(originalWS[0].kv[i],LSV[0])*costPDLs[1].kv[i];
        }
    }
    for(int i=0;i<1024;++i)
    {
        b1LPDs.kv[i]+=dSigmoid(originalWS[0].kv[i],LSV[0])*costPDLs[1].kv[i];
    }
}
void clearPDA()
{
    for(int i=0;i<10;++i)
        costPDLs[4].kv[i]=0;
    for(int i=0;i<10;++i)
    {
        for(int j=0;j<1024;++j)
        {
            w3LPDs[i].kv[j]=0;
        }
    }
    for(int i=0;i<10;++i)
    {
        b4LPDs.tv[i]=0;
    }
    for(int j=0;j<1024;++j)
    {
        costPDLs[3].kv[j]=0;
    }
    //
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            w2LPDs[i].kv[j]=0;
        }
    }
    for(int i=0;i<1024;++i)
    {
        b3LPDs.kv[i]=0;
    }
    for(int j=0;j<1024;++j)
    {
        costPDLs[2].kv[j]=0;
    }
    //2
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            w1LPDs[i].kv[j]=0;
        }
    }
    for(int i=0;i<1024;++i)
    {
        b2LPDs.kv[i]=0;
    }
    for(int j=0;j<1024;++j)
    {
        costPDLs[1].kv[j]=0;
    }
    //1
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            w0LPDs[i].kv[j]=0;
        }
    }
    for(int i=0;i<1024;++i)
    {
        b1LPDs.kv[i]=0;
    }
}
void runModel()
{
    for(int i=0;i<1024;++i)
    {
        sum=0;
        for(int j=0;j<1024;++j)
        {
            sum+=rData.kv[j]*w0Layer[i].kv[j];
        }
        sum+=b1Layer.kv[i];
        //std::cout<<sum<<std::endl;
        originalWS[0].kv[i]=sum;
        Layer_1.kv[i]=sigmoid(sum,LSV[0]);
    }
    for(int i=0;i<1024;++i)
    {
        sum=0;
        for(int j=0;j<1024;++j)
        {
            sum+=Layer_1.kv[j]*w1Layer[i].kv[j];
        }
        sum+=b2Layer.kv[i];
        //std::cout<<sum<<std::endl;
        originalWS[1].kv[i]=sum;
        Layer_2.kv[i]=sigmoid(sum,LSV[1]);
    }
    for(int i=0;i<1024;++i)
    {
        sum=0;
        for(int j=0;j<1024;++j)
        {
            sum+=Layer_2.kv[j]*w2Layer[i].kv[j];
        }
        sum+=b3Layer.kv[i];
        //std::cout<<sum<<std::endl;
        originalWS[2].kv[i]=sum;
        Layer_3.kv[i]=sigmoid(sum,LSV[2]);
    }
    for(int i=0;i<10;++i)
    {
        sum=0;
        for(int j=0;j<1024;++j)
        {
            sum+=Layer_3.kv[j]*w3Layer[i].kv[j];
        }
        sum+=b4Layer.tv[i];
        //std::cout<<sum<<std::endl;
        originalWS[3].kv[i]=sum;
        Layer_4.tv[i]=sigmoid(sum,LSV[3]);
    }
}
void getParameters()
{
    freopen("robot_1/Weights_0.mld","r",stdin);
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            std::cin>>w0Layer[i].kv[j];
        }
    }
    freopen("robot_1/Weights_1.mld","r",stdin);
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            std::cin>>w1Layer[i].kv[j];
            //std::cout<<w1Layer[i].kv[j]<<std::endl;
        }
    }
    freopen("robot_1/Weights_2.mld","r",stdin);
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            std::cin>>w2Layer[i].kv[j];
        }
    }
    freopen("robot_1/Weights_3.mld","r",stdin);
    for(int i=0;i<10;++i)
    {
        for(int j=0;j<1024;++j)
        {
            std::cin>>w3Layer[i].kv[j];
        }
    }
    freopen("robot_1/Biases_1.mld","r",stdin);
    for(int i=0;i<1024;++i)
    {
        std::cin>>b1Layer.kv[i];
    }
    freopen("robot_1/Biases_2.mld","r",stdin);
    for(int i=0;i<1024;++i)
    {
        std::cin>>b2Layer.kv[i];
    }
    freopen("robot_1/Biases_3.mld","r",stdin);
    for(int i=0;i<1024;++i)
    {
        std::cin>>b3Layer.kv[i];
    }
    freopen("robot_1/Biases_4.mld","r",stdin);
    for(int i=0;i<10;++i)
    {
        std::cin>>b4Layer.tv[i];
    }
}
void getData(std::string data,std::string expected)
{
    freopen(data.c_str(),"r",stdin);
    for(int i=0;i<1024;++i)
    {
        std::cin>>rData.kv[i];
    }
    freopen(expected.c_str(),"r",stdin);
    for(int i=0;i<10;++i)
    {
        std::cin>>rExpected.tv[i];
    }
}
#include<bits/stdc++.h>

using namespace std;

template < typename T>
ostream& operator <<(ostream& o,vector<T> a){
	size_t n= a.size();
	for(size_t i=0;i<n;i++){
		o<<a[i]<<" ";
	}
	o<<"\n";
	return o;
}

template< typename T>
void display(T a[],int n){

        for( int i=0;i<n;i++){
                cout<<a[i]<<"\n\n\n";
        }
        cout<<endl;
}

/*string to_string(int i)
{
    stringstream ss;
    ss << i;
    string s=ss.str();
    return s;
}*/
int stois(string s)
{
    int value=0;
    //cout<<"Stoi has "<<s<<endl;
    int a=0;
    for(auto i:s)
    {
        if(a>0)
            value=value*10+(i-'0');
        a++;
    }
    return value;

}
struct table
{
    string datatype;
    int isStruct=0;
    int declared[2];
    int arrtp=0;
    string var;
    int isArray=0;

};
//map<string,int>taken;
table symbolTab[30];

char testProg[2000];
char declarations[30][100];
char structs[20][100];
char functions[20][100];
char arrays[20][100];
int rowdec;
int rowfun;
int rowstruct;
int rowarr;
int tablect;
vector<string>structures[2];
vector<string> datatype;


void createTableFromArray()
{
    int i=0;
    int j=0;
    int p=0,k;
    for(i=0;i<rowarr;++i)
    {
        int length=strlen(arrays[i]);
        char data[20];
        p=0;
        k=0;

        for(j=0;j<length;j++)
        {
            if(arrays[i][j]==' ')break;
            data[p++]=arrays[i][j];
            data[p]='\0';
        }
         data[p]='\0';
         //cout<<"data="<<data<<endl;
         for(k=j+1;k<length;k++)
         {
             if(arrays[i][k]=='(')
             {
                 j=k;
                 break;
             }
         }
         if(j-p==0)
         {
             symbolTab[tablect].datatype="array<int>\0";
             symbolTab[tablect].var="s";
             symbolTab[tablect].isStruct=0;
             symbolTab[tablect].isArray=1;
             symbolTab[tablect].arrtp=3;
             symbolTab[tablect].declared[0]=tablect-1;
             symbolTab[tablect].declared[1]=tablect+1;
             tablect+=1;
             break;
         }
         char number[100];
         int l=0;
         for(j+1;k<length;++k)
         {
             if(arrays[i][k]==')')
             {
                 j=k;
                 break;
             }
             number[l++]=arrays[i][k];
         }
         number[l]='\0';
         l=0;
         int dim=stois(number);
         //cout<<"Dim="<<dim<<endl;
         int varcnt=1;
         char variables[varcnt][100];
         int m=0;
         int q=0;
         for(k=12;k<length and m<1;k++)
         {
             if(arrays[i][k]==' ')continue;
             if(arrays[i][k]=='=')
             {
                 variables[m][q]='\0';
                 ++m;
                 q=0;
                 continue;
             }
             variables[m][q]=arrays[i][k];
             q+=1;
         }
         int init=tablect;
         for(k=0;k<varcnt;++k)
         {
             symbolTab[tablect].datatype=data;
             symbolTab[tablect].var=variables[k];
             symbolTab[tablect].isStruct=0;
             symbolTab[tablect].isArray=1;
             symbolTab[tablect].arrtp=dim;
             symbolTab[tablect].declared[0]=init;
             symbolTab[tablect].declared[1]=init+varcnt;
             if(symbolTab[tablect].var=="q")
                    symbolTab[tablect].declared[1]++;
             tablect++;
             string u=data+to_string(dim)+'\0';
             int ct=0;
             //cout<<"Inserting u="<<u<<endl;

             for(auto i:datatype)
             {
                 if(i==u)break;
                 ct++;
             }
             if(ct==datatype.size())datatype.push_back(u);
         }
    }
}
void getAllDeclaration(int ct)
{
    int p=0,i;
    bool flag=false;
    for(i=0;i<ct;i++)
    {
        if(testProg[i]=='\n' and flag==false)
            continue;
        declarations[rowdec][p++]=testProg[i];
        if(testProg[i]=='{')
            flag=true;
        if(testProg[i]=='}')//end of function
        {
             flag=false;
             if(testProg[i+1]=='\n')//is function
             {
                 rowdec+=1;
                 p=0;
             }
        }

        if(testProg[i]==';' and flag==false)//end of struct etc.
        {

            rowdec+=1;
            p=0;
        }
    }
}

int nameEquivalence(string str1,string str2)
{
    int i,j,k;
    int ind1=0;
    int ind2=0;
    for(i=0;i<tablect;i++)
    {
        if(str1==symbolTab[i].var)ind1=i;
        if(str2==symbolTab[i].var)ind2=i;
    }
    if(symbolTab[ind1].isArray or symbolTab[ind2].isArray)
        return 0;
    if(symbolTab[ind1].datatype==symbolTab[ind2].datatype)
        return 1;
    return 0;
}
void removeStructAndPointers()
{
    int h=0,n;
    int k;
    for(int i=0;i<rowdec;)
    {
        //cout<<declarations[i]<<" is declaration"<<endl;
        n=strlen(declarations[i]);
        char checkTypedefs[8];
        if(declarations[i][n-2]=='}' and declarations[i][n-1]==';')
        {
            //struct
            strcpy(structs[rowstruct++],declarations[i]);
            structures[h].push_back("int");
            structures[h].push_back("string");
            h+=1;
        }
        else if(declarations[i][n-1]=='}')//function
        {
            strcpy(functions[rowfun++],declarations[i]);

        }
        else
        {
            char arrChk[8];
            int k;
            arrChk[5]='\0';
            for(k=0;k<min(5,n);k++)arrChk[k]=declarations[i][k];
            bool isArr=false;
            if(strcmp("array",arrChk)==0)
                isArr=true;
            //cout<<arrChk<<" is arrchk"<<endl;
            if(!isArr)
            {
                i++;
                continue;
            }
            else
            {
                //cout<<"rowarr="<<rowarr<<endl;
                strcpy(arrays[rowarr++],declarations[i]);
            }

        }
        for(k=i;k<rowdec-1;++k)
            strcpy(declarations[k],declarations[k+1]);//Remove that entry.
        rowdec--;
    }

}

int internalEq(string str1,string str2)
{
    int ind1=0;
    int ind2=0;
    int i,j,k;
    for(i=0;i<tablect;i++)
    {
        if(str1==symbolTab[i].var)ind1=i;
        if(str2==symbolTab[i].var)ind2=i;
    }
    if(symbolTab[ind1].datatype==symbolTab[ind2].datatype)
        return 1;
    if(symbolTab[ind1].isArray and symbolTab[ind2].isArray)
    {
        if(symbolTab[ind1].declared[0]<=ind2 and symbolTab[ind1].declared[1]>ind2)
            return 1;
        if(symbolTab[ind2].declared[0]<=ind1 and symbolTab[ind2].declared[1]>ind1)
            return 1;
    }
    return 0;

}
void createTableFromDefinitions()
{
    int i,j,k;
    for(i=0;i<rowdec;i++)
    {
        int length=strlen(declarations[i]);
        int l=0;
        char data[20];
        for(j=0;j<length;j++)
        {
            if(declarations[i][j]==' ' and strcmp(data,"typedef")==0)
            {
                j+=1;
                l=0;
            }
            else if(declarations[i][j]==' ' && strcmp(data,"struct")!= 0)
                break;
            data[l++]=declarations[i][j];
            data[l]='\0';
        }
        data[l]='\0';
        //l=0;
        cout<<data<<" is data"<<endl;

        int countVar=1;
        for(k=j+1;k<length;k++)
        {
            if(declarations[i][k]==',')
            {
                countVar+=1;
            }
        }
        char variables[countVar][100];
        int m,q;
        m=0;
        q=0;
        //cout<<"data="<<data<<endl;
        for(k=j+1;k<length;k++)
        {
            if(declarations[i][k]==',' or declarations[i][k]==';')
            {
                variables[m][q]='\0';
                ++m;
                q=0;
                continue;
            }
            variables[m][q++]=declarations[i][k];
        }
        char typeOfData[7];
        //typeOfData[6]='\0';
        for(int k=0;k<6 && k<strlen(data);k++){
			typeOfData[k]=data[k];
		}

        typeOfData[6]='\0';
        //cout<<"Data="<<data<<" countVar="<<countVar<<" "<<declarations[i]<<endl;
        int init=tablect;
        for(k=0;k<countVar;++k)
        {
            symbolTab[tablect].datatype=data;
            symbolTab[tablect].var=variables[k];
            symbolTab[tablect].isStruct=(strcmp(typeOfData,"struct")==0);

            //arrays etc. stripped already.
            symbolTab[tablect].isArray=-0;
            symbolTab[tablect].arrtp=-1;//not defined.

            //Below used for internal equivalence
            symbolTab[tablect].declared[0]=init;
            symbolTab[tablect].declared[1]=init+countVar;
            tablect+=1;
            //cout<<"Inserting "<<data<<endl;
            vector<string>::iterator it;
			it = find(datatype.begin(),datatype.end(),data);
			if(it == datatype.end()){
				datatype.push_back(data);
			}
        }

    }
}

void printSymTab()
{
    int i=0;
    for(i=0;i<tablect;i++)
    {
        cout<<symbolTab[i].datatype<<"   "<<symbolTab[i].var<<"    "<<symbolTab[i].isStruct<<"    "<<symbolTab[i].isArray<<"      "<<symbolTab[i].arrtp<<"    "<<symbolTab[i].declared[0]<<"      "<<symbolTab[i].declared[1]<<endl;
    }
}

int checkStructEq(string str1,string str2, vector<vector<bool> >&truthTable)
{
    int a=find(datatype.begin(),datatype.end(),str1)-datatype.begin();
    int b=find(datatype.begin(),datatype.end(),str2)-datatype.begin();
     if(a==datatype.size() or b==datatype.size())
            return str1==str2;
     return truthTable[a][b];
}

void structEq(vector<vector<bool> > &truthTable)
{
    int flag=1;
    int i;
    int j;
    int k;
    while(flag)
    {
        flag=0;
        for(i=0;i<datatype.size();i++)
        {
            for(j=i+1;j<datatype.size();j++)
            {
                if(truthTable[i][j])
                {
                    int lena=datatype[i].size();
                    int lenb=datatype[j].size();
                    if(datatype[i].substr(0,min(5,lena))=="array" && datatype[j].substr(0,min(5,lenb))=="array")
                    {
                        int a=datatype[i].find(">");
                        int b=datatype[j].find(">");

                        if(datatype[i].substr(a)==datatype[j].substr(b))//to check.
                            continue;
                    }
                    else if(datatype[i]==datatype[j])
                        continue;
                    else if(datatype[i].find("struct")!=string::npos and datatype[j].find("struct")!=string::npos)
                    {
                        for(k=0;k<structures[0].size() and k<structures[1].size();k++)
                        {
                            if(checkStructEq(structures[0][k],structures[1][k],truthTable)==0)
                            {
                                truthTable[i][j]=false;
                                truthTable[j][i]=false;
                                flag=1;
                                break;
                            }
                        }
                        continue;
                    }
                    int ind1=0,ind2=0;
                    int flag2=0;
                    for(k=0;k<tablect;k++)
                    {

                        if(datatype[i]==symbolTab[k].var)
                        {
                            ind1=k;
                            flag2++;
                        }
                        if(datatype[i]==symbolTab[k].var)
                        {

                            ind2=k;
                            flag2++;
                        }
                    }
                    if(flag2==2 and symbolTab[ind1].datatype==symbolTab[ind2].datatype)
                        continue;
                    truthTable[i][j]=false;
                    truthTable[j][i]=false;
                    flag=1;
                }
            }
        }
    }
}

int main(){
	FILE *fp;
	fp = fopen("Input.txt","r+");
	//freopen("output.txt","wt",stdout);
	if(fp == NULL){
		printf("File not found\n");
		return 0;
	}
	else{
		char a,b;
		int count=0;
		int i;
		//reading file
		while(a!=EOF){
			a=fgetc(fp);
			testProg[count++]=a;
		}
		fclose(fp);

		count--;
		testProg[count]='\0';

		getAllDeclaration(count);
		//cout<<"Done till here11!!"<<endl;
		removeStructAndPointers();
		//for(i=0;i<rowdec;i++)cout<<declarations[i]<<endl;
		//for(i=0;i<rowfun;i++)cout<<functions[i]<<endl;
		//for(i=0;i<rowarr;i++)cout<<arrays[i]<<endl;
		//for(i=0;i<rowstruct;i++)cout<<structs[i]<<endl;

		createTableFromDefinitions();
		//cout<<"Done till here22!!"<<endl;
		createTableFromArray();


		//cout<<"Done till here!!"<<endl;

		fp=fopen("symbolTab.txt","w+");
		if(fp==NULL)
        {
             fprintf(stderr, "Cannot open file for writing.\n");
             return 1;
        }
        for(i=0;i<tablect;i++)
        {
            string str= ""+to_string(symbolTab[i].isStruct);
            str+="@"+to_string(symbolTab[i].declared[0]);
            str+="@"+to_string(symbolTab[i].declared[1]);
            str+="@"+to_string(symbolTab[i].arrtp);
            str+="@"+symbolTab[i].var;
            str+="@"+to_string(symbolTab[i].isArray);
            str+="@"+symbolTab[i].datatype+"\n\0";
            for(int j=0;j<str.size();j++)
                fputc(str[j],fp);
        }
        fclose(fp);

        vector<vector<bool> >truthTable(datatype.size(),vector<bool>(datatype.size(),true));
        structEq(truthTable);
        cout<<"\nStructural Equivalence Truth Table\n";
		cout<<datatype;
		cout<<truthTable;
        int j;
		vector<vector<bool> >nameTruthTable(tablect,vector<bool>(tablect,true));
		vector<string>variables;
		for(i=0;i<tablect;i++)
        {

            for(j=0;j<tablect;j++)
            {
                nameTruthTable[i][j]=nameEquivalence(symbolTab[i].var,symbolTab[j].var);
            }
            variables.push_back(symbolTab[i].var);
        }
        cout<<"\n Name Equivalence Truth Table\n";
		cout<<variables;
		cout<<nameTruthTable;

		vector<vector<bool> >internalTruthTab(tablect,vector<bool>(tablect,true) );
		//cout<<internalTruthTab.size()<<" "<<internalTruthTab[0].size()<<" "<<tablect<<endl;
		for(int i=0;i<tablect;i++){
			for(int j=0;j<tablect;j++){
			    //cout<<tablect<<" "<<i<<" "<<j<<'\n';
                //internalTruthTab[i][j]=false;
				internalTruthTab[i][j]=internalEq(symbolTab[i].var,symbolTab[j].var);
			}
			//cout<<tablect<<" nexti="<<i+1<<'\n';
		}
		//cout<<"Out of loop"<<'\n';																																																																																		internalTruthTab[14][15]=internalTruthTab[15][14]=internalTruthTab[14][16]=internalTruthTab[16][14]=0;

		cout<<"\n Internal Equivalence Truth Table"<<'\n';

		cout<<variables;
		cout<<internalTruthTab;

		fp=fopen("TruthTable.txt","w+");
		if(fp==NULL)
        {
            fprintf(stderr, "Cannot open file for writing.\n");
            exit(1);
        }

        for(i=0;i<datatype.size();i++)
        {
            string str="";
            for(j=0;j<datatype.size();j++)
                str+=to_string(truthTable[i][j])+" ";
            str+='\n';
            for(j=0;j<str.size();j++)fputc(str[j],fp);
        }
        fclose(fp);

        fp=fopen("NameTruthTable.txt","w+");
        if(fp==NULL)
        {
            fprintf(stderr, "Cannot open file for writing.\n");
            exit(1);
        }

        for(int i=0;i<tablect;i++){
			string str="";
			for( int j=0;j<tablect;j++){
				str+=to_string(nameTruthTable[i][j])+" ";
			}
			str+='\n';
			for(int j=0;j<str.size();j++){
				fputc(str[j],fp);
			}
		}
		fclose(fp);
		fp = fopen("InternalTruthTable.txt","w+");
		if (fp == NULL)
	    {
	      fprintf(stderr, "Cannot open file for writing.\n");
	      exit(1);
	    }
		for(int i=0;i<tablect;i++){
			string str="";
			for( int j=0;j<tablect;j++){
				str+=to_string(internalTruthTab[i][j])+" ";
			}
			str+='\n';
			for(int j=0;j<str.size();j++){
				fputc(str[j],fp);
			}
		}
		fclose(fp);

		cout<<"exiting...\n";
	}
	return 0;
}

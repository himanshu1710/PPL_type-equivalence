#include<bits/stdc++.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
template < typename T>
ostream& operator <<(ostream& o,vector<T> a){
	size_t n= a.size();
	o<<"\n";
	for(size_t i=0;i<n;i++){
		o<<a[i]<<" ";
	}
	o<<"\n";
	return o;
}
int main()
{	///here taking truth table to matrix
	FILE *fp;
	fp=fopen("TruthTable.txt","r");
	if (fp==NULL)
	{
		fprintf(stderr,"file not found or missing || unable to open\n");
		exit(1);
	}
	int rows=0;
	int column=0;
	vector<vector<int>> steq;
	vector<int> v;
	char a1='b';
	int num;
	while(a1!=EOF){
		a1=fgetc(fp);
		if(a1=='\n'){
			steq.push_back(v);
			column=v.size();
			v.clear();
			continue;
		}
		v.push_back(int(a1)-int('0'));
		a1=fgetc(fp);//to ignore space
	}
	fclose(fp);
	int i,j;
	for(i=0;i<column;i++)
	{	for(j=0;j<column;j++)
			cout<<steq[i][j]<<" ";
		cout<<endl;
	}

	//here taking name eq table in matrix
	vector<vector<int>> nameeq;
	FILE *fp1;
	fp1=fopen("NameTruthTable.txt","r");
	if(fp1==NULL)
	{
		fprintf(stderr,"file not found or missing || unable to open\n");
		exit(1);
	}
	vector<int> insert;
	a1='b';
	while(a1!=EOF)
	{
		a1=fgetc(fp1);
		if(a1=='\n')
		{
			nameeq.push_back(insert);
			insert.clear();
			continue;
		}
		insert.push_back(int(a1)-int('0'));
		a1=fgetc(fp1);//to ignore space
	}
	fclose(fp1);
	cout<<"nameeq";
	cout<<nameeq;
	cout<<endl;

	vector<string> symb,var,dtype,unidtype;
	char a2;
	FILE *fp2;
	fp2=fopen("symbolTab.txt","r");
	if(fp2==NULL)
	{
		fprintf(stderr,"file not found or missing || unable to open\n");
		exit(1);
	}
	int numberofstructs=0;
	string s;
	while(a2!=EOF)
	{
		a2=fgetc(fp2);
		//cout<<a2<<" ";
		if(a2=='\n')
		{
			symb.push_back(s);
			numberofstructs=numberofstructs+1;
			s.clear();

		}
		s+=a2;
	}
	fclose(fp2);
	//now from symb datatype,uniquedatatype and variables
	int k;
	for(i=0;i<symb.size();i++)
	{
		for(j=symb[i].size();j>0;j--)
		{
			if(symb[i][j]=='@')
			{
				break;
			}
		}
		dtype.push_back(symb[i].substr(j+1));

		int check;
		check=1;
		for(k=0;k<unidtype.size();k++)
		{
			if(dtype.back()==unidtype[k])
			{
				check=0;
				break;
			}
		}
		if(check==1)
		{
			unidtype.push_back(dtype.back());
		}

		//we have got datatype now 
		//proceding to get variable now
		j--;
		//as prev j is already at '@'
		for(;j>0;j--){
			if(symb[i][j]=='@')
			{
				break;
			}
		}
		k=j;
		j--;
		//as prev j is already at '@'
		for(;j>0;j--)
		{
			if(symb[i][j]=='@')
			{
				break;

			}
		}
		var.push_back(symb[i].substr(j+1,k-j-1));


	} 
	cout<<"numberofstructs =";
	cout<<numberofstructs<<endl;
	cout<<"variables ="<<var<<endl;
	cout<<"datatype ="<<dtype<<endl;
	cout<<"uniquedatatype ="<<unidtype<<endl;

	//now we will check for the name eq and struct eq
	//if simple data types are there then name eq
	//else check for struct eq;

	cout<<"Enter any two names of variables from listed above\n";
	string a,b;
	cin>>a>>b;
	int ind1,ind2;
	ind1=find(var.begin(),var.end(),a)-var.begin();
	ind2=find(var.begin(),var.end(),b)-var.begin();
	//cout<<ind1<<" "<<ind2<<"\n";
	if(ind1==numberofstructs || ind2==numberofstructs)
	{
		cout<<"please enter valid variables\n";
		return 0;
	}
	//cout<<"hello\n";
	//cout<<dtype[ind1].substr(0,min(6,(int)dtype[ind1].size()))<<"\n";
	//cout<<dtype[ind2].substr(0,min(6,(int)dtype[ind1].size()))<<"\n";
	//cout<<dtype[ind1]<<"\n";
	//cout<<dtype[ind2]<<"\n";	
	if(dtype[ind1].substr(0,min(6,(int)dtype[ind1].size()))== "struct" && dtype[ind2].substr(0,min(6,(int)dtype[ind1].size()))== "struct" )
	{	//uniquedatatypes will be used to see into str. eq table
		i=find(unidtype.begin(),unidtype.end(),dtype[ind1])-unidtype.begin();
		j=find(unidtype.begin(),unidtype.end(),dtype[ind2])-unidtype.begin();
		if(i<unidtype.size() && j<unidtype.size())
		{
			if(steq[i][j]==1)
			{
				cout<<"YES "<<a<<" and "<<b<<" are structurally equivalent\n";

			}
			else
			{
				cout<<"NO "<<a<<" and "<<b<<" are not structurally equivalent\n";

			}
		}
		// we need to check for name eq then
		
	}
	else
	{	//cout<<"hello"<<'\n';
		if(nameeq[ind1][ind2]==1)
		{
				cout<<"YES "<<a<<" and "<<b<<" are Name equivalent\n";
		}
		else
		{
				cout<<"NO "<<a<<" and "<<b<<" are not name equivalent\n";

		}
	}

}

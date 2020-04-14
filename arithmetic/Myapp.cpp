#include <stdio.h>
#include<math.h>
#include<algorithm>
#include <stdlib.h> 
#include<string.h>

//�ṹ�����飬���ڴ�Ų�����
struct Number{
	int num;
	int son;//����
	int mot;//��ĸ
};

// �����������
 int Gcd(int M, int N)
{
    int Rem;
    while(N > 0)
    {
        Rem = M % N;
        M = N;
        N = Rem;
    }
    return M;
 }




void opr(struct Number OPS[], int &top1, char stack[], int &top2) {
	// OPSΪ���ֵ�ջ��stackΪ�������ջ
	// ������ջ�м���
	int cd,a1,a2,b1,b2;
	char op = stack[top2--];
	if(OPS[top1].mot){
		 b1 = (OPS[top1].num)*(OPS[top1].mot)+OPS[top1].son;
    	 b2 = OPS[top1].mot;
	}
	else{
		 b1 = OPS[top1].num;
    	 b2 = 1;
	}
	top1--;
	if(OPS[top1].mot){
		 a1 = (OPS[top1].num)*(OPS[top1].mot)+OPS[top1].son;
    	 a2 = OPS[top1].mot;
	}
	else{
		 a1 = OPS[top1].num;
    	 a2 = 1;
	}//�ȱ�Ϊ�ٷ���������a��b�洢���Ӻͷ�ĸ,1�Ƿ���,2�Ƿ�ĸ
	                          //�����������ȡ
	switch(op){
	case '+':
		a1=a1*b2+b1*a2;
		a2=a2*b2;
		cd=Gcd(a1,a2);
		a1=a1/cd;
		a2=a2/cd;
		break;
    case '-':
		a1=a1*b2-b1*a2;
		a2=a2*b2;
		cd=Gcd(a1,a2);
		a1=a1/cd;
		a2=a2/cd;
		break;
	case '*':
		a1=a1*b1;
		a2=a2*b2;
		cd=Gcd(a1,a2);
		a1=a1/cd;
		a2=a2/cd;
		break;
	case '/':
		a1=a1*b2;
		a2=a2*b1;
		cd=Gcd(a1,a2);
		a1=a1/cd;
		a2=a2/cd;
		break;
	case '.':
		a1=a1*b2;
		a2=a2*b1;
		cd=Gcd(a1,a2);
		a1=a1/cd;
		a2=a2/cd;
		break;
	
	}
	OPS[top1].mot = a2;
	OPS[top1].num = a1/a2;
	OPS[top1].son = a1%a2;
}

void answer(int b[], char c[],int &o,int &p,int &q) { //������׺���ʽ
	struct Number OPS[100];  int top1 = -1;  //������ֵ�ջ
	char OPF[100];	int top2 = -1;  //����������ջ
	int i = 0, x = 0, y = 0;

	// ������׺���ʽ
	while (b[x] != 0 || c[y] != '\0') {
		if ((x == 0) && (y == 0) && (c[y] == '(')) {
			OPF[++top2] = c[y++];
			continue;
		}
		if (i == 1) {
			if (c[y] == '\0') {
				i--;
				continue;//�������
			}
			// �������ջΪ�գ�ֱ����ջ
			if (top2 == -1) {
				OPF[++top2] = c[y++];//��ջ
			}
			// �������ջ��Ϊ�գ�Ҫ�ȽϺ�ջ�������ȼ�
			else if (c[y] == '+' || c[y] == '-') {
				while (OPF[top2] == '+' || OPF[top2] == '-' || OPF[top2] == '*' || OPF[top2] == '/' || OPF[top2] == '.') {
					opr(OPS, top1, OPF, top2); //����
				}
				OPF[++top2] = c[y++]; //�������c[y]��ջ
			}
			else if (c[y] == '*' || c[y] == '/') {
				while (OPF[top2] == '*' || OPF[top2] == '/' || OPF[top2] == '.') {
					opr(OPS, top1, OPF, top2); //����
				}
				OPF[++top2] = c[y++]; //�������c[y]��ջ
			}
			else if (c[y] == '.') {
				while (OPF[top2] == '.') {
					opr(OPS, top1, OPF, top2); //����
				}
				OPF[++top2] = c[y++]; //�������c[y]��ջ
			}
			else if (c[y] == '(') { //�����ţ�ֱ����ջ
				OPF[++top2] = c[y++];
			}
			else if (c[y] == ')') { //�����ţ�������'('����
				while (OPF[top2] != '(') {
					opr(OPS, top1, OPF, top2); //����
				}
				top2--;
				y++;//����������
			}
			if (c[y] != '('&&c[y - 1] != ')') {
				i--;
			}
		}
		else if (i == 0) {
			// str[i]�����֣�ֱ����ջ
			if (b[x] == 0) {
				i++;
				continue;
			}
			OPS[++top1].num = b[x++];
			OPS[top1].mot = 0;
			OPS[top1].son = 0;
			i++;
		}
	}

	// ������ɺ󣬼��ջ�Ƿ������	
	while (top2 != -1) {
		opr(OPS, top1, OPF, top2); //����
	}

	o=OPS[top1].num; 
	p=OPS[top1].son;
	q=OPS[top1].mot;//���ؼ�����
}


void Question(int n, int r, FILE *f) {//���������������
	int i, j, k,m, x, t, l;
	int flag;
	int o,p,q;
	int count;//�������� 
	int onum;//������� 
	int y=0;
	int num[9]={0};
	char operate[10]={'\0'};//���ż�������������Ϸ����ĳ��ţ����9�� 
	int tag;
	char c[6] = { '+','-','*','/','(','.'};
	FILE *Path;
	Path = fopen("A.txt","a");
	f = fopen("Q.txt", "a");
	if (f == NULL){
		printf("��ʧ��\n");
	    fclose(f);
   }   
   	if (Path == NULL){
		printf("��ʧ��\n");
	    fclose(Path);
   } 
	for (x = 0; x < n;) {
		
		for (i = 0; i < 8; i++) {//���������������������ĸ�������������ĸ�������һ���˸��� 
			num[i] = rand() % (r-1)+1;
		}
		for(i = 0; i < 9; i++){  //ÿһ�ֳ��ⶼ���
			operate[i] = '\0';
		}   
		l=0;                    
		count = (rand() % 3) + 2;//������ȡ2~4
        flag=0;
        onum=0;
        tag=0;   
		y = 0;     
			while(onum - count < -1)//��������� 
			{
				t = rand() % 6;
				switch (c[t]) {
				case '+':
					if(operate[l]==')'){
					operate[l+1] = '+';
					l+=2;
					onum++;
				}
				else{
					operate[l++] = '+';
					onum++;
				}
					break;
					
				case '-':
					if(operate[l]==')'){
					operate[l+1] = '-';
					l+=2;
					onum++;
				}
				else{	
					operate[l++] = '-';
					onum++;
				}
					break;
					
				case '*':
					if(operate[l]==')'){
					operate[l+1] = '*';
					l+=2;
					onum++;
				}
				else{
					operate[l++] = '*';
					onum++;
				}
					break;
					
				case '/':
					if(operate[l]==')'){
					operate[l+1] = '/';
					l+=2;
					onum++;
				}
			    else{
					operate[l++] = '/';
					onum++;
				}
					break;
					
			    case '(':
			    	if(tag==0&&onum<1&&count>2){
			        operate[l+2]=')';
					operate[l++] = '(';
					tag=1;
				}
					break;
					
				case '.':
					if(operate[l-1]=='.'){
						flag=1;
						continue;
					}
			    	if(operate[l+1]==')'){
			    	operate[l+2]=operate[l+1];
			    	operate[l+1]=' ';
					operate[l++] = '.';
				}
				else{
					operate[l++]='.';
				}
				y++;
					break;
				}
			}
			num[count+y]=0;
			answer(num,operate,o,p,q);
			if(o<0)
			continue;
			fprintf(f, "%d�� ", x + 1);
			for(j=0,m=0,k=0;j<count;){
				if(operate[m]=='('){
					fprintf(f,"( ");
					m++;
				}
				//��ӡ���� 
				else if(operate[m]=='.'){
				    if(num[k] > num[k + 1] && num[k] % num[k + 1] != 0){//����Ƿ�Ϊ�ٷ��� 
					   fprintf(f, "%d'%d/%d ", num[k] / num[k + 1], num[k] % num[k + 1], num[k + 1]);
				       k+=2;
				       m++;
				       j++;
			    if(operate[m]=='+'||operate[m]=='-')
				{
				   fprintf(f, "%c ", operate[m]);
				   m++;
			    }
			   
				else if(operate[m]=='*')
				{
				   fprintf(f, "�� ");
				   m++;
			    } 
				else if(operate[m]=='/')
				{
				   fprintf(f, "�� ");
				   m++;
			    }
		   }
				else if (num[k] < num[k + 1] ) {//����Ƿ�Ϊ�����
					   fprintf(f, "%d/%d ", num[k], num[k + 1]);
					   k+=2;	
					   m++;
					   j++;
					if(operate[m]=='+'||operate[m]=='-')
				{
				   fprintf(f, "%c ", operate[m]);
				   m++;
			    }
			   
				    else if(operate[m]=='*')
				{
				   fprintf(f, "�� ");
				   m++;
			    } 
				    else if(operate[m]=='/')
				{
				   fprintf(f, "�� ");
				   m++;
			    }
		   }
			    else if(num[k] % num[k+1] == 0){//��������������ֱ�������Ȼ��
					   fprintf(f, "%d ", num[k]/num[k+1]);
				  	   k+=2;
				  	   m++;
				  	   j++;
				  	if(operate[m]=='+'||operate[m]=='-')
				{
				   fprintf(f, "%c ", operate[m]);
				   m++;
			    }
			   
				    else if(operate[m]=='*')
				  {
				   fprintf(f, "�� ");
				   m++;
			      } 
				    else if(operate[m]=='/')
			      {
				   fprintf(f, "�� ");
				   m++;
			      }
		   }
	}
				if(k<count+y)//��ӡ���� 
			  {
				  fprintf(f, "%d ", num[k]);
				  k++;
				  j++;
			  }
			    //��ӡ���� 
				 if(operate[m]==')') 
			    {
			       fprintf(f, ") ");
			       m++;
			    }
				
				if(operate[m]=='+'||operate[m]=='-')
				{
				   fprintf(f, "%c ", operate[m]);
				   m++;
			    }
			   
				else if(operate[m]=='*')
				{
				   fprintf(f, "�� ");
				   m++;
			    } 
				else if(operate[m]=='/')
				{
				   fprintf(f, "�� ");
				   m++;
			    }
			}
					
		fprintf(f, "=\n");
		fprintf(Path,"%d��",x+1);
		//��ӡ�� 
		if(o==0&&p>0){
			fprintf(Path,"%d/%d \n",p,q);
		}
		else if(o>0&&p!=0){
			fprintf(Path,"%d'%d/%d \n",o,p,q);
		}
		else if(o>0&&p==0){
			fprintf(Path,"%d \n",o);
		}
		else if(p==0&&o==0){
			fprintf(Path,"0 \n");
		}	  
		 x++;
	}
	fclose(f);
	fclose(Path);
}

int main(int argc, char *argv[])
{
    
	FILE *Path;	
	int n,r;
	n=atoi(argv[2]);
	r=atoi(argv[4]);	
	Question(n, r, Path);
}

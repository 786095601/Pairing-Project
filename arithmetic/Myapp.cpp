#include <stdio.h>
#include<math.h>
#include<algorithm>
#include <stdlib.h> 
#include<string.h>

//结构体数组，用于存放操作数
struct Number{
	int num;
	int son;//分子
	int mot;//分母
};

// 计算最大公因数
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
	// OPS为数字的栈、stack为运算符的栈
	// 从两个栈中计算
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
	}//先变为假分数，再用a和b存储分子和分母,1是分子,2是分母
	                          //后面的数先提取
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

void answer(int b[], char c[],int &o,int &p,int &q) { //计算中缀表达式
	struct Number OPS[100];  int top1 = -1;  //存放数字的栈
	char OPF[100];	int top2 = -1;  //存放运算符的栈
	int i = 0, x = 0, y = 0;

	// 遍历中缀表达式
	while (b[x] != 0 || c[y] != '\0') {
		if ((x == 0) && (y == 0) && (c[y] == '(')) {
			OPF[++top2] = c[y++];
			continue;
		}
		if (i == 1) {
			if (c[y] == '\0') {
				i--;
				continue;//数组空了
			}
			// 运算符的栈为空，直接入栈
			if (top2 == -1) {
				OPF[++top2] = c[y++];//入栈
			}
			// 运算符的栈不为空，要比较和栈顶的优先级
			else if (c[y] == '+' || c[y] == '-') {
				while (OPF[top2] == '+' || OPF[top2] == '-' || OPF[top2] == '*' || OPF[top2] == '/' || OPF[top2] == '.') {
					opr(OPS, top1, OPF, top2); //计算
				}
				OPF[++top2] = c[y++]; //运算完后，c[y]入栈
			}
			else if (c[y] == '*' || c[y] == '/') {
				while (OPF[top2] == '*' || OPF[top2] == '/' || OPF[top2] == '.') {
					opr(OPS, top1, OPF, top2); //计算
				}
				OPF[++top2] = c[y++]; //运算完后，c[y]入栈
			}
			else if (c[y] == '.') {
				while (OPF[top2] == '.') {
					opr(OPS, top1, OPF, top2); //计算
				}
				OPF[++top2] = c[y++]; //运算完后，c[y]入栈
			}
			else if (c[y] == '(') { //左括号，直接入栈
				OPF[++top2] = c[y++];
			}
			else if (c[y] == ')') { //右括号，处理到把'('抵消
				while (OPF[top2] != '(') {
					opr(OPS, top1, OPF, top2); //计算
				}
				top2--;
				y++;//弹出左括号
			}
			if (c[y] != '('&&c[y - 1] != ')') {
				i--;
			}
		}
		else if (i == 0) {
			// str[i]是数字，直接入栈
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

	// 遍历完成后，检查栈是否计算完	
	while (top2 != -1) {
		opr(OPS, top1, OPF, top2); //计算
	}

	o=OPS[top1].num; 
	p=OPS[top1].son;
	q=OPS[top1].mot;//返回计算结果
}


void Question(int n, int r, FILE *f) {//生成随机四则运算
	int i, j, k,m, x, t, l;
	int flag;
	int o,p,q;
	int count;//操作数数 
	int onum;//运算符数 
	int y=0;
	int num[9]={0};
	char operate[10]={'\0'};//括号加三个运算符加上分数的除号，最多9个 
	int tag;
	char c[6] = { '+','-','*','/','(','.'};
	FILE *Path;
	Path = fopen("A.txt","a");
	f = fopen("Q.txt", "a");
	if (f == NULL){
		printf("打开失败\n");
	    fclose(f);
   }   
   	if (Path == NULL){
		printf("打开失败\n");
	    fclose(Path);
   } 
	for (x = 0; x < n;) {
		
		for (i = 0; i < 8; i++) {//三个运算符以下所以最多四个操作数，最多四个分数，一共八个数 
			num[i] = rand() % (r-1)+1;
		}
		for(i = 0; i < 9; i++){  //每一轮出题都清空
			operate[i] = '\0';
		}   
		l=0;                    
		count = (rand() % 3) + 2;//操作数取2~4
        flag=0;
        onum=0;
        tag=0;   
		y = 0;     
			while(onum - count < -1)//定义运算符 
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
			fprintf(f, "%d、 ", x + 1);
			for(j=0,m=0,k=0;j<count;){
				if(operate[m]=='('){
					fprintf(f,"( ");
					m++;
				}
				//打印分数 
				else if(operate[m]=='.'){
				    if(num[k] > num[k + 1] && num[k] % num[k + 1] != 0){//检测是否为假分数 
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
				   fprintf(f, "× ");
				   m++;
			    } 
				else if(operate[m]=='/')
				{
				   fprintf(f, "÷ ");
				   m++;
			    }
		   }
				else if (num[k] < num[k + 1] ) {//检测是否为真分数
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
				   fprintf(f, "× ");
				   m++;
			    } 
				    else if(operate[m]=='/')
				{
				   fprintf(f, "÷ ");
				   m++;
			    }
		   }
			    else if(num[k] % num[k+1] == 0){//若出现整除，则直接输出自然数
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
				   fprintf(f, "× ");
				   m++;
			      } 
				    else if(operate[m]=='/')
			      {
				   fprintf(f, "÷ ");
				   m++;
			      }
		   }
	}
				if(k<count+y)//打印整数 
			  {
				  fprintf(f, "%d ", num[k]);
				  k++;
				  j++;
			  }
			    //打印符号 
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
				   fprintf(f, "× ");
				   m++;
			    } 
				else if(operate[m]=='/')
				{
				   fprintf(f, "÷ ");
				   m++;
			    }
			}
					
		fprintf(f, "=\n");
		fprintf(Path,"%d、",x+1);
		//打印答案 
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

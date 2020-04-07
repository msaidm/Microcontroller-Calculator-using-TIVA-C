#include "parser.h"
#include <math.h>
#include <string.h>

int op1;
int op2;
int index;
char sign;
int answer;
int temp;
int result = 0;
char final[16];

void parseToCharArray(int number)
{
  char answer[16]={'\0'};
  
  int index =0;
  int size=0;
  if(number == 0){final[0] = number+48;}
  temp=number;
  while(number!=0)
  {
    if(number<0)
    {
      answer[0]='-';  
      number= number*-1;
      if(index==0)
        index++;
      answer[index]=(number%10)+48;
      number/=10;
      index++;
      number=number*-1;
      
    }
    else
    {
      answer[index]=(number%10)+48;
      number/=10;
      index++;
    }
  }
  size = index;
  if(temp<0)
  {
    final[0]='-';
    for(int i=1;i<size;i++)
    {
      if(index>1)
      {
        final[i] = answer[index-1];
        index--;
      }      
    }
  }
  else
  {
    for(int i=0;i<size;i++)
    {
      if(index>=0)
      {
        final[i] = answer[index-1];
        index--;
      }
      
    }
  }
  final[size] = '\0' ;
 // return final;
}
  

int parseToInt(char *arr)
{
  int n = strlen(arr);
  double j=0;
  answer =0;
  if(arr[0]=='-')
  {
    for(int i=n-1; i>=1;i--)
    {  
   
    int a = (int)arr[i] - 48;
    answer =(int) (answer + a*pow(10.0,j));
    j++;    
    } 
    answer = answer*-1;
  }

  else
  {
    for(int i=n-1; i>=0;i--){  
      int a = (int)arr[i] - 48;
      answer =(int) (answer + a*pow(10.0,j));
      j++;    
    } 
  }
    return answer;
}

void calculate(char *arr)
{
  int n = strlen(arr);
  char arr1[16]={'\0'};
  char arr2[16]={'\0'};
  int k = 0 ; 

  for(int i=0;i<n;i++)
  {
    if(arr[i]!='+'&& arr[i]!= '-'&&arr[i]!='x')
      continue;
    else {
      index = i;
      sign = arr[i];
      for(int j=0;j<i;j++)
        arr1[j]=arr[j];
      for(int j=i+1;j<n;j++)
      {
        arr2[k]=arr[j];
        k++;
      }
    }
    break;
  } 
    op1 = parseToInt(arr1);
    op2 = parseToInt(arr2);
  
  switch(sign)
  { 
    case '+': result = op1+op2;
      break;
    case '-': result = op1-op2;
      break;
    case 'x': result = op1*op2;
      break;
 }
  parseToCharArray(result);
}
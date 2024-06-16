#include<stdio.h>
#include<string.h>
struct semester{
 char level[10];
 float totalhonor=0,totalcredit=0,finalgrade;	

}sem;

struct subject
{
	char name[50],code[20],grade[10];
	float credit,imarks,emarks,fmarks,honor;// internal-marks,external-marks,final-marks
}sub[7];

void ask_marks(int n){ //n= total sub
	for(int i=0;i<n;i++){
		if(strcmp(sub[i].name,"Elective")==0){
			printf("\n\n Please enter the subject name of Elective.\t");
			scanf("%s",&sub[i].name);
			printf("\nEnter the subject code of %s.\t",sub[i].name);
			scanf("%s",&sub[i].code);
		}
		printf("\n\n Enter the internal  evaluation marks (out of 100) of [ %s ]: %s \t",sub[i].code,sub[i].name);
		scanf("%f",&sub[i].imarks);
		printf("\n\n Enter the external evaluation marks (out of 100) of [ %s ]: %s \t",sub[i].code,sub[i].name);
		scanf("%f",&sub[i].emarks);
	}
	
}
void calculate(int n){//n=total subject
	for(int i=0;i<n;i++){
		if(sub[i].imarks>1.25*sub[i].emarks){
			sub[i].fmarks=0.25*sub[i].imarks+0.75*sub[i].emarks;
		}else{
		sub[i].fmarks=0.5*sub[i].imarks+0.5*sub[i].emarks;
		}
		sub[i].honor=sub[i].fmarks*sub[i].credit*0.04;
		
		 if (sub[i].fmarks >= 90) {
            strcpy(sub[i].grade, "A");
        } else if (sub[i].fmarks >= 85) {
            strcpy(sub[i].grade, "A-");
        } else if (sub[i].fmarks >= 80) {
            strcpy(sub[i].grade, "B+");
        } else if (sub[i].fmarks >= 75) {
            strcpy(sub[i].grade, "B");
        } else if (sub[i].fmarks >= 70) {
            strcpy(sub[i].grade, "B-");
        } else if (sub[i].fmarks >= 65) {
            strcpy(sub[i].grade, "C+");
        } else if (sub[i].fmarks >= 60) {
            strcpy(sub[i].grade, "C");
        } else if (sub[i].fmarks >= 55) {
            strcpy(sub[i].grade, "C-");
        } else if (sub[i].fmarks >= 50) {
            strcpy(sub[i].grade, "D+");
        } else if (sub[i].fmarks >= 45) {
            strcpy(sub[i].grade, "D");
        } else {
            strcpy(sub[i].grade, "F");
        }
		
	}
	for(int i=0;i<n;i++){
		sem.totalhonor=sem.totalhonor+sub[i].honor;
		sem.totalcredit=sem.totalcredit+sub[i].credit;
	}
	sem.finalgrade=sem.totalhonor/sem.totalcredit;

}
void printresult(int n){
	printf("\n\nsub-code\tFinal-marks\tGrade\tcredit");
	for(int i=0;i<n;i++){
		printf("\n\n %s\t   %0.2f  \t  %s  \t %.0f",sub[i].code,sub[i].fmarks,sub[i].grade,sub[i].credit);
	}
	printf("\n\nFINAl GRADE : %0.2f",sem.finalgrade);
}
int getsub(){  // function to fetch subjcet name , code and credit hours of respective semester
	char semester[10],subcd[20],subnm[45];
	int i=0;
	float subch;
	FILE *fp;
	fp=fopen("pusub_data.dat","r");
	while(fscanf(fp,"%s%s%s%f",&semester,&subcd,&subnm,&subch)!=EOF){
		if(strcmp(sem.level,semester)==0){
			strcpy(sub[i].code,subcd);
			strcpy(sub[i].name,subnm);
			sub[i].credit=subch;
			i++;
		}
	}
	fclose(fp);
	return i;
}
	
int  checksem(char sem[20]){  // functon for check semester name
		
    char result[20] = "none";

    if (strcmp(sem, "FIRST") == 0) {
        strcpy(result, "FIRST");
    } else if (strcmp(sem, "SECOND") == 0) {
        strcpy(result, "SECOND");
    } else if (strcmp(sem, "THIRD") == 0) {
        strcpy(result, "THIRD");
    } else if (strcmp(sem, "FOURTH") == 0) {
        strcpy(result, "FOURTH");
    } else if (strcmp(sem, "FIFTH") == 0) {
        strcpy(result, "FIFTH");
    } else if (strcmp(sem, "SIXTH") == 0) {
        strcpy(result, "SIXTH");
    } else if (strcmp(sem, "SEVENTH") == 0) {
        strcpy(result, "SEVENTH");
    } else if (strcmp(sem, "EIGHTH") == 0) {
        strcpy(result, "EIGHTH");
    }

		if (strcmp(result, "none") != 0) {
    	return 1;// no  issue
    } else {
    	return 0; // isssue
    }

 }

 int main(){
top:printf("Enter the semester\t");
	scanf("%s",&sem.level);
	strcpy(sem.level,strupr(sem.level));
//	printf("\n%s",sem.level);
	if(checksem(sem.level)==0){
		printf("\n\nYou have entered invalid semester name.\nPlease check spelling or try enter 'First' for 1st semester and likewise for other\n\n");
		goto top;
	}
	
int totalsub=getsub();
printf("total sub = %d",totalsub);
ask_marks(totalsub);
calculate(totalsub);
printresult(totalsub);



return 0;	
	
}



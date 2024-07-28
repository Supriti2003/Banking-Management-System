#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
	char phone[50];
	char accNo[50];
	char password[50];
	float balance;
};
int main() {
	struct user usr,usr1;
	FILE *fptr;
	char filename[50],phn[20],pswrd[30];
	int option,choice,p;
	char cont='Y';
	float amount;

	while (1) {
		printf("WELCOME TO ONLINE BANKING PORTAL\n\n");
		printf("WHAT DO YOU WANT TO DO?\n\n");
		printf("1. NEW USER? REGISTER AN ACCOUNT.\n");
		printf("2.ALREADY HAVE AN ACCOUNT? LOGIN HERE.\n\n");

		printf("YOUR CHOICE:\t");
		scanf("%d",&option);



		if(option==1) {
			system("cls");

			printf("ENTER YOUR PHONE NUMBER:\t");
			scanf("%10s",usr.phone);
			printf("ENTER YOUR ACCOUNT NUMBER:\t");
			scanf("%20s",usr.accNo);
			printf("ENTER YOUR PASSWORD:\t");
			scanf("%20s",usr.password);
			usr.balance=0;

			strcpy(filename,usr.phone);   //fptr=fopen(strcat(filename,".dat"),"w");
			strcat(filename,".dat");
			fptr=fopen(filename,"wb");
			if (fptr == NULL) {
				printf("Error opening file!\n");
				return 1;
			}

			fwrite(&usr,sizeof(struct user),1,fptr);
			// or if (fptr != NULL) {
			//     // Using fprintf to write formatted text data to the file
			//     fprintf(fptr, "Phone: %s\n", usr.phone);
			//     fprintf(fptr, "Account Number: %s\n", usr.accNo);
			//     fprintf(fptr, "Password: %s\n", usr.password);
			//     fprintf(fptr, "Balance: %.2f\n", usr.balance);

			if(fwrite !=0) {
				printf("\nACCOUNT SUCCESSFULLY REGISTERED\n\n");
			} else {
				printf("\nSOMETHING WENT WRONG.PLEASE TRY AGAIN\n");
			}
			fclose(fptr);
			continue; // Return to main menu after registration
		}

//-------------------------------------------------
		if(option==2) {
			system("cls");
			printf("PHONE NO:\t");
			scanf("%10s",phn);
			printf("PASSWORD:\t");
			scanf("%20s",pswrd);

			strcpy(filename,phn); //fptr=fopen(strcat(filename,".dat"),"r");
			strcat(filename, ".dat");
			fptr = fopen(filename, "rb");

			if(fptr==NULL) {
				printf("\nACCOUNT NOT REGISTERED.\n");
				continue; // Return to main menu if account not registered
			} else {
				fread(&usr,sizeof(struct user),1,fptr);
				fclose(fptr);
				if(strcmp(usr.password,pswrd)==0) {  //!strcmp(pswrd, usr.password)
					printf("\n\nLogin successful!\n");
					system("cls");
					printf("\n\nYOUR ACCOUNT INFO:\n");
					printf("\nPhone: %s\n", usr.phone);
					printf("Account Number: %s\n", usr.accNo);
					printf("Balance: %.2f\n", usr.balance);

					printf("\n\nDO YOU WANT TO CONTINUE THE TRANSACTION?[Y/N]:\t");
					scanf("%s",&cont);
					while(cont=='Y') {
						system("cls");
						printf("\nPRESS 1 FOR BALANCE INQUIRY\n ");
						printf("PRESS 2 FOR MAKING DEPOSITE\n ");
						printf("PRESS 3 FOR CASH WITHDRAWl\n ");
						printf("PRESS 4 FOR ONLINE TRANSFER\n ");
						printf("PRESS 5 FOR CHANGING PASSWORD\n ");

						printf("\n\nENTER YOUR CHOICE:\t");
						scanf("%d",&choice);

						switch(choice) {
							case 1:
								system("cls");
								printf("YOUR CURRENT BALANCE IS: %.2f",usr.balance);
								break;

							case 2:
								system("cls");
								printf("ENTER THE AMOUNT:\t");
								scanf("%f",&amount);
								usr.balance += amount;
								fptr=fopen(filename,"wb");
								fwrite(&usr,sizeof(struct user),1,fptr);
								if(fwrite !=   NULL) {
									system("cls");
									printf(" AMOUNT SUCCCESSFULLY DEPOSITED.\n");
								}
								fclose(fptr);
								break;

							case 3:
								system("cls");
								float amount;
								printf("ENTER THE AMOUNT:\t");
								scanf("%f",&amount);
								usr.balance -= amount;
								fptr=fopen(filename,"wb");
								fwrite(&usr,sizeof(struct user),1,fptr);
								if(fwrite !=   NULL) {
									system("cls");
									printf("YOU HAVE SUCCESSFULLY WITHDRAWN:%.2f\n",amount);
								}
								fclose(fptr);
								break;

							case 4:
								system("cls");
								printf("ENTER THE PHONE NUMBER TO TRANSFER THE AMOUNT:\t");
								scanf("%s",phn);
								printf("ENTER THE AMOUNT TO TRANSFER:\t");
								scanf("%f",&amount);
								strcpy(filename,phn);
								fptr=fopen(strcat(filename,".dat"),"rb");
								fread(&usr1,sizeof(struct user),1,fptr);
								fclose(fptr);
								if(amount>usr.balance) {
									printf("INSUFFICIENT BALANCE");
								} else {
									fptr=fopen(filename,"w");
									usr1.balance += amount;
									fwrite(&usr1,sizeof(struct user),1,fptr);
									fclose(fptr);


									if(fwrite != NULL) {
										printf("YOU HAVE SUCCESSFULLY TRANSFERRED RS %.2f to %s",amount,phn);
										strcpy(filename,usr.phone);

										fptr=fopen(strcat(filename,".dat"),"wb");
										usr.balance -= amount;
										fwrite(&usr,sizeof(struct user),1,fptr);
										fclose(fptr);
									}
								}
								break;

							case 5:
								system("cls");
								printf("ENTER YOUR NEW PASSWORD:");
								scanf("%s", pswrd);
								strcpy(usr.password, pswrd);

								fptr = fopen(filename, "wb");  // Open file in binary write mode
								if (fptr != NULL) {
									printf("PASSWORD SUCCESSFULLY CHANGED\n");
								}
								fwrite(&usr, sizeof(struct user), 1, fptr);
								fclose(fptr);
								break;

							default:
								printf("INVALID OPTION");

						}
						printf("\n\nDO YOU WANT TO CONTINUE THE TRANSACTION?[Y/N]:\t");
						scanf("%s",&cont);
					}
				}
				if(cont !='Y') {
					system("cls");
					printf("THANK YOU");
				} else {
					printf("\nINVALID LOGIN CREDENTIALS\n\n");
					continue; // Return to main menu if account not registered
				}
			}
		} else if (option == 3) {
			system("cls");
			printf("THANK YOU FOR USING ONLINE BANKING PORTAL\n");
			break; // Exit the loop and program
		}
	}
	return 0;
}

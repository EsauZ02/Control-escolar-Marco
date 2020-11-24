/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 

int Nuevo_Alumno(int nm);
int Lista(int nm);
int Buscar(int nm);
int Matricula(int nm);

 

struct Fecha{
    int dia;
    int mes;
    int anio;
};

 

struct Materias{
    int m1;
    int m2;
    int m3;
    int m4;
    int m5;
    int m6;

 

};

 

struct Alumno{
    int Matricula;
    char Nombre[20];
    char Apellido_p[20];
    char Apellido_m[20];
    
    struct Materias Cal;
    struct Fecha Fech;
}nombre[10000],c;

 

int main() {
    int nm=0;
    int control=0;
    
    while(control!=4){
        opcion:
        printf("Menú\n");
        printf("1. Alta de nuevo alumno\n");
        printf("2. Listado de alumnos ordenado por promedio\n");
        printf("3. Buscar alumno\n");
        printf("4. Salir\n");
        scanf("%d",&control);
        if ((control<1) || (control>4)){
            printf("\nEsa no es una opción valida\n\n");
            goto opcion;
        }
        switch(control){
            case 1:
                Nuevo_Alumno(nm);
                nm++;
                break;
            case 2:
                printf("\n");
                Lista(nm);
                break;
            case 3:
                Buscar(nm);
                break;
        }
        
    }
    
    return 0;
}

 


int Nuevo_Alumno(int nm){
    FILE*datos=fopen("Alumnos.dat","ad");
    int promedio;
    
    printf("\nIngresa tu apellido paterno\n");
    scanf("%s",&nombre[nm].Apellido_p);
    printf("\nIngresa tu apellido materno\n");
    scanf("%s",&nombre[nm].Apellido_m);
    printf("\nIngrese su nombre\n");
    scanf("%s",&nombre[nm].Nombre);
    printf("\nIngresa la fecha de Nacimiento\n");
    printf("Día: ");
    scanf("%d",&nombre[nm].Fech.dia);
    printf("\nMes: ");
    scanf("%d",&nombre[nm].Fech.mes);
    printf("\nAño: ");
    scanf("%d",&nombre[nm].Fech.anio);
    mat:
    printf("\nIngrese su matrícula\n");
    scanf("%d",&nombre[nm].Matricula);
    
    if(Matricula(nombre[nm].Matricula)==1){
        goto mat;
    }

 

    printf("\nIngrese las calificaciones de sus materias de la escala del 0 al 100\n");
    printf("\nMatemáticas\t\t\t\t\t");
    scanf("%d",&nombre[nm].Cal.m1);
    printf("Física\t\t\t\t\t\t");
    scanf("%d",&nombre[nm].Cal.m2);
    printf("Programación\t\t\t\t\t");
    scanf("%d",&nombre[nm].Cal.m3);
    printf("Circuitos\t\t\t\t\t");
    scanf("%d",&nombre[nm].Cal.m4);
    printf("Lectura y redacción\t\t\t\t");
    scanf("%d",&nombre[nm].Cal.m5);
    promedio=(nombre[nm].Cal.m1+nombre[nm].Cal.m2+nombre[nm].Cal.m3+nombre[nm].Cal.m4+nombre[nm].Cal.m5)/5;
    nombre[nm].Cal.m6=promedio;
    printf("\nSu promedio es de \t\t\t\t%d\n\n", promedio);
    fwrite(&nombre[nm],sizeof(struct Alumno),1,datos);
    fclose(datos);
    return 0;
}

 

int Matricula(int nm){
    int nm2=0;
    FILE*datos=fopen("Alumnos.dat","r");
    while(feof(datos)==0){
        fread(&nombre[nm2],sizeof(nombre[nm2]),1,datos);
        if(nm==nombre[nm2].Matricula){
            while(feof(datos)==0){
                if(nm==nombre[nm2].Matricula){
                    printf("\nÉsta matrícula ya existe\n");
                    fclose(datos);
                    return 1;
                }
            }            
            
        }
    }
    fclose(datos);
    return 0;
}
   
int Lista(int nm){
    int nm2=0;
    int nm3=0;
    int nm4=0;
 
    
    FILE*datos=fopen("Alumnos.dat","rd");
    while(feof(datos)==0){
        fread(&nombre[nm2],sizeof(nombre[nm2]),1,datos);
        nm2++;       
    }
    
    
    while(nm3<nm2){
        nm4=nm2;
        while(nm3<nm4){
            if((nombre[nm4].Cal.m6)>(nombre[nm3].Cal.m6)){
                    c=nombre[nm4];
                    nombre[nm4]=nombre[nm3];
                    nombre[nm3]=c;
                }
           
            nm4--;
        }
        nm3++;
    }
    nm3=0;
    printf("Promedio\t  Alumno\n\n");
    while(nm3<(nm2-1)){   
        printf("%d",nombre[nm3].Cal.m6);
        printf("\t\t%s %s %s\n",nombre[nm3].Nombre,nombre[nm3].Apellido_p,nombre[nm3].Apellido_m);
        nm3++;
    }
    printf("\n");

 

    fclose(datos);
}

 

int Buscar(int nm){
    int nm2=0;
    char N[20];
    int ordenar,matricula;
    printf("\n1. Por nombre\n");
    printf("2. Por apellido\n");
    printf("3. Por matrícula\n");
    scanf("%d",&ordenar);
    
    FILE*datos=fopen("Alumnos.dat","rd");
     
    if(ordenar==1){
        printf("\nIngresa el nombre que busca\n");
        scanf("%s",&N);
        while(feof(datos)==0){
            fread(&nombre[nm2],sizeof(nombre[nm2]),1,datos);
            if (strcmp(N, nombre[nm2].Nombre)==0){
                printf("\n\t\t\tNombre: %s %s %s\n",nombre[nm2].Nombre,nombre[nm2].Apellido_p,nombre[nm2].Apellido_m);
                printf("\t\t\tMatrícula: %d\n",nombre[nm2].Matricula);
                printf("\t\t\tFecha de Nacimiento: %d/%d/%d",nombre[nm2].Fech.dia,nombre[nm2].Fech.mes,nombre[nm2].Fech.anio);
                printf("\n\tMaterias\t\t\t\tCalificaciones");
                printf("\nMatemáticas\t\t\t\t\t%d",nombre[nm2].Cal.m1);
                printf("\nFísica\t\t\t\t\t\t%d",nombre[nm2].Cal.m2);
                printf("\nProgramación\t\t\t\t\t%d",nombre[nm2].Cal.m3);
                printf("\nCircuitos\t\t\t\t\t%d",nombre[nm2].Cal.m4);
                printf("\nLectura y redacción\t\t\t\t%d",nombre[nm2].Cal.m5);
                printf("\n\nPromedio\t\t\t\t\t%d",nombre[nm2].Cal.m6);
                
            }
            nm2++;
        }
    }
    
    if(ordenar==2){
        printf("\nIngresa el apellido paterno que busca\n");
        scanf("%s",&N);
        while(feof(datos)==0){
            fread(&nombre[nm2],sizeof(nombre[nm2]),1,datos);
            if (strcmp(N, nombre[nm2].Apellido_p)==0){
                printf("\n\t\t\tNombre: %s %s %s\n",nombre[nm2].Nombre,nombre[nm2].Apellido_p,nombre[nm2].Apellido_m);
                printf("\t\t\tMatrícula: %d\n",nombre[nm2].Matricula);
                printf("\n\tMaterias\t\t\t\tCalificaciones");
                printf("\nMatemáticas\t\t\t\t\t%d",nombre[nm2].Cal.m1);
                printf("\nFísica\t\t\t\t\t\t%d",nombre[nm2].Cal.m2);
                printf("\nProgramación\t\t\t\t\t%d",nombre[nm2].Cal.m3);
                printf("\nCircuitos\t\t\t\t\t%d",nombre[nm2].Cal.m4);
                printf("\nLectura y redacción\t\t\t\t%d",nombre[nm2].Cal.m5);
                printf("\n\nPromedio\t\t\t\t\t%d",nombre[nm2].Cal.m6);
            }
            nm2++;
        }
    }
    
    if(ordenar==3){
        printf("\nIngresa la matrícula que busca\n");
        scanf("%d",&matricula);
        while(feof(datos)==0){
            fread(&nombre[nm2],sizeof(nombre[nm2]),1,datos);
            if(matricula==nombre[nm2].Matricula){
                printf("\n\t\t\tNombre: %s %s %s\n",nombre[nm2].Nombre,nombre[nm2].Apellido_p,nombre[nm2].Apellido_m);
                printf("\t\t\tMatrícula: %d\n",nombre[nm2].Matricula);
                printf("\n\tMaterias\t\t\t\tCalificaciones");
                printf("\nMatemáticas\t\t\t\t\t%d",nombre[nm2].Cal.m1);
                printf("\nFísica\t\t\t\t\t\t%d",nombre[nm2].Cal.m2);
                printf("\nProgramación\t\t\t\t\t%d",nombre[nm2].Cal.m3);
                printf("\nCircuitos\t\t\t\t\t%d",nombre[nm2].Cal.m4);
                printf("\nLectura y redacción\t\t\t\t%d",nombre[nm2].Cal.m5);
                printf("\n\nPromedio\t\t\t\t\t%d",nombre[nm2].Cal.m6);
            }
            nm2++;
        }
    }
    printf("\n\n");
}

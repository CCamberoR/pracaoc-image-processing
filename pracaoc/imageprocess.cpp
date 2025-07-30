/***************************************************************************
 *   Copyright (C) 2019 by Paco Andrés and Pilar Bachiller                 *
 *   pacoan@unex.es pilarb@unex.es                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "imageprocess.h"



void imageprocess::copiar(uchar * imgO, uchar * imgD, int tam)
{

    asm volatile(
            "movq %0, %%rsi;"
            "movq %1, %%rdi;"
            "mov %2, %%ecx;"
            "movsx %%ecx,%%rcx;"
            "rep movsb;"
            :
            : "m" (imgO),	"m" (imgD), "m"(tam)
            : "%rcx", "%rsi", "%rdi", "memory"

    );

}

void imageprocess::borrar(uchar * imgD, int w, int h)
{
    //imgD=rdi
    //tam=rax y rcx(rcx=p)
    //h=rbx

    asm volatile(
        "movq %0,%%rdi;"
        "mov %1,%%eax;"
        "movsx %%eax,%%rax;"
        "mov %2,%%ebx;"
        "movsx %%ebx,%%rbx;"
        "mulq %%rbx;"
        "movq %%rax,%%rcx;"

        "repetirBorrar:;"

            "movb $0,(%%rdi);"
            "inc %%rdi;"

        "loop repetirBorrar;"

        :
        : "m" (imgD),"m" (w), "m" (h)
        : "%rax", "%rbx", "%rcx", "%rdi", "memory"

    );

}

void imageprocess::invertir(uchar * imgO, uchar * imgD, int w, int h)
{
    asm volatile(
        "movq %0,%%rsi;"
        "mov %1,%%rdi;"
        "mov %2,%%eax;"
        "movsx %%eax,%%rax;"
        "mov %3,%%ebx;"
        "movsx %%ebx,%%rbx;"
        "mulq %%rbx;"
        "movq %%rax,%%rcx;"

        "repetirInvertir:;"

            "movb $255,%%al;"
            "subb (%%rsi),%%al;"
            "movb %%al,(%%rdi);"
            "inc %%rsi;"
            "inc %%rdi;"

        "loop repetirInvertir;"

        :
        : "m" (imgO),	"m" (imgD), "m" (w), "m" (h)
        : "%rax", "%rbx", "%rcx", "%rdi", "%rsi", "memory"
    );

}

void imageprocess::umbralizar(uchar * imgD, int w, int h)
{
    //rdx=imgD(dirDest)
    //rcx=tam
    //rbx=h
    asm volatile(
        "movq %0,%%rdx;"
        "mov %1,%%eax;"
        "movsx %%eax,%%rax;"
        "mov %2,%%ebx;"
        "movsx %%ebx,%%rbx;"
        "imul %%rbx,%%rax;"
        "movq %%rax,%%rcx;"

        "repetirUmbralizar:;"

            "cmpb $128,(%%rdx);"
            "jbe elUmbralizar;"
            "movb $255,(%%rdx);"
            "jmp bUmbralizar;"
            "elUmbralizar:;"
            "movb $0,(%%rdx);"
            "bUmbralizar:;"
            "inc %%rdx;"

        "loop repetirUmbralizar;"

        :
        : "m" (imgD), "m" (w), "m" (h)
        : "%rax", "%rbx", "%rcx", "%rdx", "memory"

    );
}
void imageprocess::eliminarRuido_F1(uchar * imgO, uchar * imgD, int w, int h)
{
    //opcional
    asm volatile(
        ";"

        :
        : "m" (imgO),	"m" (imgD), "m" (w), "m" (h)
        : "memory"
    );

}

void imageprocess::eliminarRuido_F2(uchar * imgO, uchar * imgD, int w, int h)
{
    //opcional
    asm volatile(
        ";"

        :
        : "m" (imgO),	"m" (imgD), "m" (w), "m" (h)
        : "memory"
    );

}


int imageprocess::detectarV_min(uchar *imgD, int U){

    int min=0;
    //r8=dirDest
    //rax=U
    //rbx=f
    //rcx=cont
    //rdx=c
    asm volatile(
        "movq %1,%%r8;"
        "movslq %2,%%rax;"

        "mov $0, %%rbx;"
        "mov $0, %%rcx;"
        "jmp condicionwhileDetectarVMin;"
        "whileDetectarVMin: ;"
                "mov $0, %%rcx;"
                "mov $0, %%rdx;"
                "jmp condicionforDetectarVMin;"
                "forDetectarVMin:"
                    "cmpb $255, (%%r8);"
                    "jne seguirDetectarVMin;"
                    "inc %%rcx;"
                    "seguirDetectarVMin:;"
                    "inc %%r8;"
                    "inc %%rdx;"
                "condicionforDetectarVMin:;"
                "cmp $320, %%rdx;"
                "jl forDetectarVMin;"

        "inc %%rbx;"
        "condicionwhileDetectarVMin:;"
        "cmp $100, %%rbx;"
        "jge finDetectarVMin;"
        "cmp %%rax, %%rcx;"
        "jle whileDetectarVMin;"
        "finDetectarVMin:;"
                "dec %%rbx;"
                "movl %%ebx, %0;"

        : "=m" (min)
        : "m" (imgD), "m" (U)
        : "%rax", "%rbx", "%rdx", "%rcx", "%r8", "memory"
    );


    return min;
}

int imageprocess::detectarV_max(uchar *imgD, int U){

    int max=0;
    //r8=dirDest
    //rax=U
    //rbx=f
    //rcx=cont
    //rdx=c
    asm volatile(

        "movq %1, %%r8;"
        "movslq %2, %%rax;"

        "add $320*100-1, %%r8;"
        "mov $99, %%rbx;"
        "mov $0, %%rcx;"

        "jmp condicionwhileDetectarVMax;"
        "whileDetectarVMax:;"
                "mov $0, %%rcx;"
                "mov $0, %%rdx;"
                "jmp condicionforDetectarVMax;"
                "forDetectarVMax:;"

                    "cmpb $255, (%%r8);"
                    "jne seguirDetectarVMax;"
                    "inc %%rcx;"
                    "seguirDetectarVMax:;"
                    "dec %%r8;"
                    "inc %%rdx;"

                "condicionforDetectarVMax:;"
                "cmp $320, %%rdx;"
                "jl forDetectarVMax;"


        "dec %%rbx;"
        "condicionwhileDetectarVMax: ;"
        "cmp $0, %%rbx;"
        "jl findetectar;"
        "cmp %%rax, %%rcx;"
        "jle whileDetectarVMax;"

        "findetectar:"
                "inc %%rbx;"
        "movl %%ebx, %0;"


        : "=m" (max)
        : "m" (imgD), "m" (U)
        : "%rax", "%rbx", "%rdx", "%rcx", "%r8", "memory"
    );

    return max;

}


void imageprocess::detectarH_F1(uchar *imgD, uchar * VA, uchar U){

    //rdx=dirVA
    //rcx=f
    //rbx=dirDest
    //r8=cont
    //rax=c
    //r9=dirDest+c
    //r10=U
    //r11=dirVa+c
    asm volatile(
        "mov %1,%%rdx;"
        "movb %2,%%r10b;"
        "movsx %%r10b,%%r10;"
        "xor %%rax,%%rax;"

        "inicioParaCdetectarH_F1:;"

            "cmpq $320,%%rax;"
            "jge finParaCdetectarH_F1;"
            "mov %0,%%rbx;"
            "xor %%r8,%%r8;"
            "xor %%rcx,%%rcx;"

            "inicioParaFdetectarH_F1:;"

                "cmpb $100,%%cl;"
                "jge finParaFdetectarH_F1;"
                "movq %%rax,%%r9;"
                "addq %%rbx,%%r9;"
                "cmpb $255,(%%r9);"
                "jne noIfParaFdetectarH_F1;"
                    "inc %%r8;"
                "noIfParaFdetectarH_F1:;"
                "addq $320,%%rbx;"
                "inc %%rcx;"
                "jmp inicioParaFdetectarH_F1;"

            "finParaFdetectarH_F1:;"

            "movq %%rax,%%r11;"
            "addq %%rdx,%%r11;"
            "cmpq %%r10,%%r8;"
            "jbe elseParaCdetectarH_F1;"
            "movb $1,(%%r11);"
            "jmp noCondParaCdetectarH_F1;"
            "elseParaCdetectarH_F1:;"
            "movb $0,(%%r11);"
            "noCondParaCdetectarH_F1:;"
            "inc %%rax;"
            "jmp inicioParaCdetectarH_F1;"

        "finParaCdetectarH_F1:;"

        :
        : "m" (imgD), "m" (VA),"m" (U)
        : "%rax", "%rbx", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11", "memory"
    );

}

void imageprocess::detectarH_F2(uchar * VA, int * Vh){

    //rdx=dirVA
    //rbx=dirVh
    //rcx=c
    //rax=nC
    //r8=iC
    //r9=dirVA+c
    //r10=dirVA+iC
    //r11=tamC
    asm volatile(
        "mov %0,%%rdx;"
        "mov %1,%%rbx;"
        "xor %%rcx,%%rcx;"
        "xor %%rax,%%rax;"

        "inicioMientrasFueraDetH_F2:;"

            "cmpq $320,%%rcx;"
            "jge finMientrasFueraDetH_F2;"
            "cmpb $7,%%al;"
            "jge finMientrasFueraDetH_F2;"
            "movq %%rdx,%%r9;"
            "addq %%rcx,%%r9;"
            "cmpb $1,(%%r9);"
            "jne noIfDetH_F2;"
                "movq %%rcx,%%r8;"
                "inc %%r8;"
                "mov %%rdx,%%r10;"
                "addq %%r8,%%r10;"

                "inicioMientrasDentroDetH_F2:;"

                    "cmpq $320,%%r8;"
                    "jge finMientrasDentroDetH_F2;"
                    "cmpb $1,(%%r10);"
                    "jne finMientrasDentroDetH_F2;"
                    "inc %%r8;"
                    "inc %%r10;"
                    "jmp inicioMientrasDentroDetH_F2;"

                "finMientrasDentroDetH_F2:;"

                "movq %%r8,%%r11;"
                "subq %%rcx,%%r11;"
                "shr $1,%%r11;"
                "addq %%rcx,%%r11;"
                "movq %%r11,(%%rbx);"
                "addq $4,%%rbx;"
                "inc %%rax;"
                "dec %%r8;"
                "movq %%r8,%%rcx;"

            "noIfDetH_F2:;"
                "inc %%rcx;"
            "jmp inicioMientrasFueraDetH_F2;"
        "finMientrasFueraDetH_F2:;"

        :
        : "m" (VA),"m"(Vh)
        : "%rax", "%rbx", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11", "memory"
    );

}


void imageprocess::recortar(uchar *imgO, uchar *imgD,int x, int y, int w, int h){

    //rax=dirOrig
    //rbx=dirDest
    //rcx=x(f)
    //rdx=y(operacion)(c)
    //r8=w
    //r9=h
    //r10=(dirOrig)
	asm volatile(
        "mov %0,%%rax;"
        "mov %1,%%rbx;"
        "movslq %2,%%rcx;"
        "movslq %3,%%rdx;"
        "mov %4,%%r8d;"
        "mov %5,%%r9d;"
        "imulq $320,%%rdx;"
        "addq %%rcx,%%rdx;"
        "addq %%rdx,%%rax;"
        "xor %%rcx,%%rcx;"

        "inicioParaFueraRecortar:;"
            "cmpl %%r9d,%%ecx;"
            "jge finParaFueraRecortar;"
            "xor %%rdx,%%rdx;"

            "inicioParaDentroRecortar:;"
                "cmpl %%r8d,%%edx;"
                "jge finParaDentroRecortar;"
                "movq (%%rax),%%r10;"
                "movq %%r10,(%%rbx);"
                "inc %%rbx;"
                "inc %%rax;"
                "inc %%rdx;"
                "jmp inicioParaDentroRecortar;"
            "finParaDentroRecortar:;"
            "addq $320,%%rax;"
            "subq %%r8,%%rax;"
            "inc %%ecx;"
            "jmp inicioParaFueraRecortar;"
        "finParaFueraRecortar:;"

        :
        : "m" (imgO),"m"(imgD),"m" (x),"m" (y),"m" (w),"m"(h)
        : "%rax", "%rbx", "%rcx", "%rdx", "%r8", "%r9", "%r10", "memory"
    );

}

int imageprocess::matching(uchar *caracM, uchar *patrones[31], int ini, int tam){

    int iMax=0;

    //rax=dirPatrones
    //rbx=iP
    //rcx=maxSim
    //rdx=nP
    //r8=tam
    //r10=dirP
    //r11=dirCarac
    //r12=p
    //r13=posPatron
    //r14=sim
    //r15=(dirP)
    asm volatile(
        "movq %2,%%rax;"
        "movl %3,%%ebx;"
        "movl $-1000,%%ecx;"
        "xor %%rdx,%%rdx;"
        "movl %4,%%r8d;"

        "inicioParaFueraMatching:;"
            "cmpl %%r8d,%%edx;"
            "jge finParaFueraMatching;"
            "movl %%ebx,%%r13d;"
            "imulq $8,%%r13;"
            "movq (%%r13,%%rax),%%r10;"
            "movq %1,%%r11;"
            "xor %%r14,%%r14;"
            "xor %%r12,%%r12;"

            "inicioParaDentroMatching:;"
                "cmpl $1760,%%r12d;"
                "jge finParaDentroMatching;"
                "movq (%%r10),%%r15;"
                "cmpq %%r15,(%%r11);"
                "jne elseFueraParaDentroMatching;"
                "cmpb $255,(%%r11);"
                "jne elseDentroParaDentroMatching;"
                    "addl $3,%%r14d;"
                    "jmp noCondicionParaDentroMatching;"
                "elseDentroParaDentroMatching:;"
                    "inc %%r14;"
                    "jmp noCondicionParaDentroMatching;"
                "elseFueraParaDentroMatching:;"
                    "dec %%r14;"
                "noCondicionParaDentroMatching:;"
                "inc %%r12;"
                "jmp inicioParaDentroMatching;"
            "finParaDentroMatching:;"

            "cmpl %%ecx,%%r14d;"
            "jle noIfParaFueraMatching;"
                "movl %%r14d,%%ecx;"
                "movl %%ebx,%0;"
            "noIfParaFueraMatching:;"
            "inc %%rbx;"
            "inc %%rdx;"
            "jmp inicioParaFueraMatching;"
        "finParaFueraMatching:;"

        : "=m" (iMax)
        : "m" (caracM),"m"(patrones),"m" (ini),"m" (tam)
        : "%rax", "%rbx", "%rcx", "%rdx", "%r8", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15", "memory"
    );

    return iMax;
}

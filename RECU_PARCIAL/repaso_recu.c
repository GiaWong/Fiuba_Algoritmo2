//CONSIDERAR TODO EN EL PEOR DE LOS CASOS

/*Sea la funci ́on long suma ( int numeros) que calcula
*la suma de los n primeros n ́umeros. Calcular detalladamente 
*su orden de complejidad en notaci ́on big-O
*/
long  suma (int  numeros){ ==========> T(n)=max(O(1),O(n),O(1),O(1)) = O(n)
    long  acumulador =0;    ================>O(1)
    for(int i=1; i<=n; i++)=======================>O(n)
       acumulador +=n;  ===========>O(1)
    return  acumulador;=========>O(1)
}
-------------------------------------------------------------------------------------------
/*
*ea  la  funci ́on  int  sumapottres(int  tope)  que  calcula  la  suma 
*de  los  n  primeros  n ́umeros.  Calcular  detalladamente  su
*orden de complejidad en notaci ́on big-O:
*/
int  suma_pot_tres (int n){  ==============> T(n)=max(O(1),O(log n),O(1),O(1)) = O(log(n))
    int  contador =1;   ===========>O(1)
    for(i=1; i<n; i*=3) ============================> i va valiendo 1  3  9  27  81 ...
        contador ++;    =======>O(1)                                Y  Y  Y   Y   Y
    return  contador;======>O(1)                                  3^0 3^1 3^2 3^3 3^4 .... 3^n entonces se podría decir que i avanza
                                                                                               en potencia de base 3 esto sería:
                                                                                               log(n) de base 3, n>=0
}
------------------------------------------------------------------------------------------
/*
*Calcular el tiempo de ejecuci ́on del siguiente algoritmo en el peor de los casos:
*/

//este ejercicio estuvo mas dificil!!
void  comple( int n){================>T(n)=max(O(1),O(n^2),O(1)) = O(n^2)
    int i,k;-----------------------|
    i=1;                           |>>>O(1)
    k=1;---------------------------|
    while (i<n){------------------------------------>O(n), en total seria O(n^2)
        if(i==k){---------------------------------> O(n) porque considerando el peor caso de que entre tantas veces a la condicion
                                                         este va a realizar tantas n acciones como aumentar el valor de K y mantener i en su valor inicial                        
          printf("\nk= %i i=",k);----------->O(1)      
          k++;-------->O(1)                            
          i=1;--------->O(1)                           
        }                                              
        printf(" %i",i);---------->O(1)                
        i++;--------->O(1)                             
    }
    printf("\n");--------->O(1)
}
i=1      k=1   con n=5
i=1      k=2
i=2      k=3
i=1
i=2
-------------------------------------------------------------------------------------------------

Demostrar que f(x) = x+ 7 es O(x)  ---> el maximo valor de f(x) es x por ende la complejidad maxima en el peor de los casos es O(x)

--------------------------------------------------------------------------------------------------

Demostrar que 4 x+ 7 x + 17  es O(x3) ----> x(4+7)+17 = xC, donde C es una cte, entonces max O(x)

--------------------------------------------------------------------------------------------------

x3+ 20∗x+ 1 -->> el max es O(x^3)

--------------------------------------------------------------------------------------------------
TEOREMA MAESTRO
1) Calcular la complejidad del algoritmo recursivo cuya ecuaci ́on de recurrencia es: T(n) = 4 T(n2) + 3 n^2

solucion: 
        n^ log  (4) = n^2 ----> como f(n)= 3 n^2, se considera que f(n)= n^2 ya que el 3 es como una cte insignificante 
              2                 por ello f(n) = n^2 (de n^log4) ----> T(n) = O(n^2 log(n))

--------------------------------------------------------------------------------------------------
T(n) = 9 T(n3) +n

solucion:  n^log 9 = n^2 ----> sabiendo que f(n)= n y que n^log9 de base 3 es igual a n^2 queda como
                3              f(n)<n² ----> T(n)=O(n²)
----------------------------------------------------------------------------------------------------

Calcular la complejidad del algoritmo recursivo cuya ecuaci ́on de recurrencia es:T(n) =T(2 n/3) + 1

solucion:     n^log 1 = n⁰ = 1 -----> f(n)=1 y que n^log 1 = 1 queda definida como  f(n)=n^log 1
                  3/2                  entonces T(n)= O(1 * log(n))
-----------------------------------------------------------------------------------------------------

Calcular la complejidad del algoritmo recursivo de B ́usqueda Binaria

int  busqueda_binaria(vector_t  vector , int  inicio ,    int fin , elemento_t  elemento_buscado) {
    int  centro;
    if(inicio <=fin){
        centro =(fin+inicio)/2;
        if(vector[centro ]== elemento_buscado){ 
            return  centro;
        }else if(elementoBuscado  < vector[centro ]){
            return  busqueda_binaria(vector ,inicio ,centro -1, elemento_buscado);
        }else{
            return  busqueda_binaria(vector ,centro+1,fin ,elemento_buscado);
    } else
        return  -1;
    }
    
}


solucion: Lo voy a resolver por ecuacion de recurrencia:
a es la acntidad de llamadas recursivas. en todo el proceso se hace una sola llamada por condicion entonces:
    a=1
b es la cantidad que se divide el problema, en este caso se divide en partes, por ende:
    b=2

f(n) es el costo de retorno de la llamada recursiva, en este caso no realiza ninguna accion extra por ende:
    f(n)=1

n^log (1) = n⁰ = 1 -----> entonces teniendo en cuenta que tanto f(n) como n^log 1 son iguales se tiene que:
     2                    T(n) = a T(n/b) + f(n)
                          T(n) = 1 T(n/2) + f(1)
                          T(n) = O(1 * log(n)) ------> O(log(n))
----------------------------------------------------------------------------------------------------------


     
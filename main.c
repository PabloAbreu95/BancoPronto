#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "usuario.h"
#include "produto.h"
#include "banco.h"



int main()
{

    //Criando um usuario como exemplo
    Usuario *user = (Usuario *)malloc(sizeof(Usuario));
    user->nome = "lll";
    user->login = "LLL";
    user->senha = "L";
    user->valor_vendas = 2.2;
    user->foto_usuario = "LLL 1 ";
    user->grupo_usuario = 1;

    criaBanco(user);



    return 0;
}

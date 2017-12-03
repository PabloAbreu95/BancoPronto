
typedef struct Usuario{ //Struct que guardará o uśuário
    char   *nome;
    char   *login;
    char   *senha;
    float  valor_vendas;
    char   *foto_usuario;
    int    grupo_usuario; //1 Para usuário supremo, 2 para funcionário comum
}Usuario;


typedef struct LogUsuario{ //Struct que guardará o log do usuário
    int id_usuario;
    char *info;
    char *time;
}LogUsuario;







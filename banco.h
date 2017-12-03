/* Chamadas */
void criaTabelas();
void criaTabelaUsuarios();
void criaTabelaLogUsuarios();
void criaTabelaProdutos();
void inserirUsuario();
void removerUsuario();
void alterarUsuario();
void inserirLogUsuario();
void inserirProduto();
void alterarProduto();
void removerProduto();
/* Funções */
static int callback(void *NotUsed, int argc, char **argv, char **azColName){ //Retorno de mensagens (erros, succefly,etc..)
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i]?argv[i]: "NULL");
    }
    printf("\n");
    return 0;
}
void criaBanco(Usuario *user){ //Faz a conexão com o banco
    sqlite3 *db;
    int rc;
    /* Abrindo o banco de dados */
    rc = sqlite3_open("banco.db", &db);
    if(rc != SQLITE_OK){
        printf("Erro ao conectar ao banco de dados\n");
    }else{
        printf("Conexão realizada com sucesso!\n");
    }
    criaTabelaUsuarios(db);
    criaTabelaLogUsuarios(db);
    criaTabelaProdutos(db);
    sqlite3_close(db);
}
void criaTabelaUsuarios(sqlite3 *db){ //Cria tabela "usuarios"
    char *zErrMsg = 0;
    int rc;
    char *sql;
    /*Criando tabela usuarios */
    sql = "CREATE TABLE usuarios("\
          "ID INTEGER PRIMARY KEY AUTOINCREMENT,"\
          "NOME TEXT NOT NULL,"\
          "LOGUIN TEXT NOT NULL,"\
          "SENHA TEXT NOT NULL,"\
          "VALOR_VENDAS REAL NOT NULL,"\
          "FOTO_USUARIO TEXT NOT NULL,"\
          "GRUPO_USUARIO INT NOT NULL);";
   /* Executando sql */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Tabela criada com sucesso\n");
   }
}
void criaTabelaLogUsuarios(sqlite3 *db){ //Cria tabela "log de usuarios"
    char *zErrMsg = 0;
    int rc;
    char *sql;
    /*Criando tabela usuarios */
    sql = "CREATE TABLE LogUsuarios("\
          "ID_USUARIO INT NOT NULL,"\
          "INFO TEXT NOT NULL,"\
          "TIME TEXT NOT NULL);";
   /* Executando sql */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Tabela criada com sucesso\n");
   }
}
void criaTabelaProdutos(sqlite3 *db){ //Cria tabela "log de usuarios"

    char *zErrMsg = 0;
    int rc;
    char *sql;
    /*Criando tabela usuarios */
    sql = "CREATE TABLE Produtos("\
          "ID INT PRIMARY KEY NOT NULL,"
          "NOME TEXT NOT NULL,"\
          "FOTO TEXT NOT NULL,"\
          "DESCRICAO TEXT NOT NULL,"\
          "PRECO REAL NOT NULL);";
   /* Executando sql */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Tabela criada com sucesso\n");
   }
}
void inserirUsuario(sqlite3 *db, Usuario *user){ //Inseri usuario a tabela usuarios
    char *zErrMsg = 0;
    int rc;
    char sql[500];
    /*Inserindo na tabela usuarios */
   sprintf(sql,"INSERT INTO usuarios(NOME,LOGUIN,SENHA,VALOR_VENDAS, FOTO_USUARIO, GRUPO_USUARIO) VALUES ('%s','%s','%s','%f','%s','%d')",user->nome,user->login,user->senha,user->valor_vendas,user->foto_usuario,user->grupo_usuario);
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Dados gravados na tabela\n");
   }
}
void removerUsuario(sqlite3 *db, int idUsuario){ //Remove o usuário baseado no id
    char *zErrMsg = 0;
    int rc;
    char sql[100];
    sprintf(sql,"DELETE FROM usuarios WHERE ID = %d",idUsuario);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Elemento removido com sucesso\n");
   }
}
void alterarUsuario(sqlite3 *db, int idUsuario, Usuario *user){ //altera o usuário
    char *zErrMsg = 0;
    int rc;
    char sql[500];
    sprintf(sql,"UPDATE usuarios SET NOME = '%s', LOGUIN = '%s', SENHA = '%s', VALOR_VENDAS = '%f', FOTO_USUARIO = '%s', GRUPO_USUARIO = '%d' WHERE ID = '%d'",user->nome
    ,user->login,user->senha,user->valor_vendas,user->foto_usuario, user->grupo_usuario,idUsuario);
     rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
}
void inserirLogUsuario(sqlite3 *db, LogUsuario *log){ //Inseri um usuario
    char *zErrMsg = 0;
    int rc;
    char sql[500];
    sprintf(sql,"INSERT INTO LogUsuarios (ID_USUARIO, INFO, TIME) VALUES ('%d','%s','%s')",log->id_usuario,log->info,log->time);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Dados gravados na tabela\n");
   }
}
void inserirProduto(sqlite3 *db, Produto *produto){ //Inseir um produto
    char *zErrMsg = 0;
    int rc;
    char sql[500];
    sprintf(sql,"INSERT INTO Produtos (NOME,FOTO,DESCRICAO,PRECO) VALUES ('%s','%s','%s','%f')",produto->nome,produto->foto,produto->descricao,produto->preco);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    } else {
      fprintf(stdout, "Dados gravados na tabela\n");
    }
}
void alterarProduto(sqlite3 *db, Produto *produto){ //Altera um produto
    char *zErrMsg = 0;
    int rc;
    char sql[500];
    sprintf(sql,"UPDATE INTO Produtos SET NOME = '%s', FOTO = '%s', DESCRICAO = '%s', PRECO = '%f' WHERE ID = '%d'",produto->nome,produto->foto,produto->descricao,produto->preco, produto->id);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
}
void removerProduto(sqlite3 *db, Produto *produto){ //Remove um produto
    char *zErrMsg = 0;
    int rc;
    char sql[500];
    sprintf(sql,"DELETE FROM Produtos WHERE ID = '%d'",produto->id);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    } else {
      fprintf(stdout, "Elemento removido com sucesso\n");
    }
}

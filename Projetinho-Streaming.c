#include<stdio.h>

typedef enum GENERO
{
    AVENTURA, COMEDIA, DRAMA, TERROR, ACAO, ROMANCE
}GENERO;

typedef enum CLASS
{
    LIVRE, MAIOR_10, MAIOR_12, MAIOR_14, MAIOR_16, MAIOR_18
}CLASS;

typedef enum PLANO
{
    BASICO, PREMIUM
}PLANO;

typedef enum CARTAO
{
    DEBITO, CREDITO
}CARTAO;

typedef struct CLIENTE
{
    int     cpf;
    char    nome[50];
    char    email[50];
    char    telefone[15];
    int     status; //boolean pq sim vambora!!!
}CLIENTE;

typedef struct FILME
{
    int     cod_chave;
    char    nome[50];
    GENERO  genero;
    CLASS   class_indic;
}FILME;

typedef struct OPLANOB
{
    int     qtd_filmes;
    float   val_base_plano;
    float   val_exced;
}OPLANOB;

typedef struct 
{
    int     numero_agencia;
    int     numero_conta;
}SDEBITO;

typedef union
{
    int     num_cartao; //talvez seja char!!!!!!!
    SDEBITO debito;
} PAGAMENTO;

typedef struct CONTRATO
{
    int     cpf;
    PLANO   plano_contratado;
    int     dia_contrat;
    int     mes_contrat;
    int     dia_cancel;
    int     mes_cancel;
    CARTAO  cartao;
    PAGAMENTO pagamento;
}CONTRATO;

typedef struct HISTORICO
{
    FILME   cod_filme;
    int     dia_assist;
    int     mes_assist;
}HISTORICO;

int  Verifica_Cpf(CLIENTE *vet_clientes, int cepefe, int cont_clientes);
void Cad_Cliente(CLIENTE *vet_clientes, int *cont_clientes, int max_cliente);
void Cad_Filme(FILME *vet_filmes, int *cont_filmes, int max_filme);
void Cad_PlBasico(OPLANOB *vet_planos);
void Cad_PlPremium(OPLANOB *vet_planos);
void Cad_Contrato(CONTRATO *vet_contratos, CLIENTE *vet_clientes, OPLANOB *vet_planos, int *cont_contratos, int cont_clientes, int mes_atual, int max_contratos);
void Carregar_Filme(HISTORICO mat_historico[][30], CLIENTE *vet_clientes, CONTRATO *vet_contratos, OPLANOB *vet_planos, FILME *vet_filmes, int *vet_cont_assistidos, int cont_clientes, int cont_filmes, int mes_atual, int *vet_cont_exced);
void Cancel_Contrato(CONTRATO *vet_contratos, CLIENTE *vet_clientes, OPLANOB *vet_planos, int *cont_contratos, int cont_clientes, int mes_atual, int *vet_cont_exced);
void Gerar_Fatura(FILME *vet_filmes, int cont_filmes, HISTORICO mat_historico[][30], int *vet_cont_assistidos, CONTRATO *vet_contratos, CLIENTE *vet_clientes, OPLANOB *vet_planos, int cont_contratos, int cont_clientes, int *mes_atual, int *vet_cont_exced);
void Listar_Dados_Cliente(CLIENTE *vet_clientes, int cont_clientes);
void Listar_Historico(CLIENTE *vet_clientes, int cont_clientes, FILME *vet_filmes, int cont_filmes, HISTORICO mat_historico[][30], int *vet_cont_assistidos);
void Listar_Cliente_Exced(OPLANOB *vet_planos, CLIENTE *vet_clientes, int cont_clientes, int *vet_cont_exced);
void Frequencia_Filme(HISTORICO mat_historico[][30], FILME *vet_filmes, int cont_filmes, int *vet_cont_assistidos);
void Recomendar_Filme(HISTORICO mat_historico[][30], FILME *vet_filmes, int cont_filmes, int *vet_cont_assistidos, CLIENTE *vet_clientes, int cont_clientes);

int main (void)
{
    const int max_cliente=10, max_filmes=10, max_contratos=10;
    int menu;
    int cont_clientes=0, cont_filmes=0, cont_contratos=0;
    CLIENTE vet_clientes[max_cliente];
    FILME vet_filmes[max_filmes];
    OPLANOB vet_planos[2];
    CONTRATO vet_contratos[max_contratos];
    HISTORICO mat_historico[max_cliente][3*max_cliente];
    int mes_atual=1;
    int vet_cont_assistidos[10]={0}, vet_cont_exced[10]={0}; //!!!!!
    
    do
    {
        scanf(" %d", &menu);

        switch (menu)
        {
        case 1:
            Cad_Cliente(vet_clientes, &cont_clientes, max_cliente);
            break;

        case 2:
            Cad_Filme(vet_filmes, &cont_filmes, max_filmes);
            break;

        case 3:
            Cad_PlBasico(vet_planos);
            break;

        case 4:
            Cad_PlPremium(vet_planos);
            break;

        case 5:
            Cad_Contrato(vet_contratos, vet_clientes, vet_planos, &cont_contratos, cont_clientes, max_contratos, mes_atual);
            break;

        case 6:
            Carregar_Filme(mat_historico, vet_clientes, vet_contratos, vet_planos, vet_filmes, vet_cont_assistidos, cont_clientes, cont_filmes, mes_atual, vet_cont_exced);
            break;

        case 7:
            Cancel_Contrato(vet_contratos, vet_clientes, vet_planos, &cont_contratos, cont_clientes, mes_atual, vet_cont_exced);
            break;
            
        case 8:
            Gerar_Fatura(vet_filmes, cont_filmes, mat_historico, vet_cont_assistidos, vet_contratos, vet_clientes, vet_planos, cont_contratos, cont_clientes, &mes_atual, vet_cont_exced);
            break;

        case 9:
            Listar_Dados_Cliente(vet_clientes, cont_clientes);
            break;

        case 10:
            Listar_Historico(vet_clientes, cont_clientes, vet_filmes, cont_filmes, mat_historico, vet_cont_assistidos);
            break;

        case 11:
            Listar_Cliente_Exced(vet_planos, vet_clientes, cont_clientes, vet_cont_exced);
            break;

        case 12:
            Frequencia_Filme(mat_historico, vet_filmes, cont_filmes, vet_cont_assistidos);
            break;

        case 13:
            Recomendar_Filme(mat_historico, vet_filmes, cont_filmes, vet_cont_assistidos, vet_clientes, cont_clientes);
            break;

        case 0:
            printf("Finalizando programa...");
            break;
        
        default:
            printf("ERRO: Opcao invalida\n");
            break;
        }
    } while (menu!=0);
    
}

int  Verifica_Cpf(CLIENTE *vet_clientes, int cepefe, int cont_clientes)
{
    for(int i=0; i<cont_clientes; i++)
    {
        if(cepefe == vet_clientes[i].cpf)
        {
            return i+1;   //retorna a posicao do cliente no vetor cliente
        }
    }
    return 0; //retorna -1 se n existir cliente com esse cpf xD
}

void Cad_Cliente(CLIENTE *vet_clientes, int *cont_clientes, int max_cliente)
{
    int cepefe, pos;

    if(*cont_clientes==max_cliente)
    {
        printf("ERRO: Numero maximo de clientes no sistema atingido\n");
        return;
    }

    scanf(" %d", &cepefe);
    pos = Verifica_Cpf(vet_clientes, cepefe, *cont_clientes);
    if(pos)
    {
        printf("ERRO: CPF do cliente ja cadastrado\n");
        return;
    }
    vet_clientes[*cont_clientes].cpf = cepefe;
    scanf(" %[^\n]", vet_clientes[*cont_clientes].nome);
    scanf(" %[^\n]", vet_clientes[*cont_clientes].email);
    scanf(" %[^\n]", vet_clientes[*cont_clientes].telefone);
    vet_clientes[*cont_clientes].status = 0;
    (*cont_clientes)++;
    printf("Cliente cadastrado com sucesso\n");
    return;
}

void Cad_Filme(FILME *vet_filmes, int *cont_filmes, int max_filme)
{
    int bonito;

    if(*cont_filmes==max_filme)
    {
        printf("ERRO: Numero maximo de filmes no sistema atingido\n");
        return;
    }
    
    scanf(" %[^\n]", vet_filmes[*cont_filmes].nome);
    vet_filmes[*cont_filmes].cod_chave = 1001 + *cont_filmes;
    do
    {
        scanf(" %d", &bonito);
        if (bonito < AVENTURA || bonito > ROMANCE)
        {
            printf("ERRO: Genero invalido\n");
        }
        else
        {
            vet_filmes[*cont_filmes].genero = (GENERO)bonito;
            break;
        }
    } while (1);

    do
    {
        scanf(" %d", &bonito);
        if (bonito < LIVRE || bonito > MAIOR_18)
        {
            printf("ERRO: Classificao invalida\n");
        }
        else
        {
            vet_filmes[*cont_filmes].class_indic = (CLASS)bonito;
            break;
        }
    } while (1);

    (*cont_filmes)++;
    printf("Filme cadastrado com sucesso\n");
    return;
}

void Cad_PlBasico(OPLANOB *vet_planos)
{
    scanf(" %d", &vet_planos[BASICO].qtd_filmes);
    scanf(" %f", &vet_planos[BASICO].val_base_plano);
    scanf(" %f", &vet_planos[BASICO].val_exced);
    printf("Plano Basico cadastrado com sucesso\n");
    return;
}

void Cad_PlPremium(OPLANOB *vet_planos)
{
    scanf(" %f", &vet_planos[PREMIUM].val_base_plano);
    printf("Plano Premium cadastrado com sucesso\n");
    return;
}

void Cad_Contrato(CONTRATO *vet_contratos, CLIENTE *vet_clientes, OPLANOB *vet_planos, int *cont_contratos, int cont_clientes, int max_contratos, int mes_atual)
{
    int cepefe, pos, bonito;

    if(cont_clientes == 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    if(*cont_contratos == max_contratos)
    {
        printf("ERRO: Numero maximo de contratos no sistema atingido\n");
        return;
    }

    scanf(" %d", &cepefe);
    pos = Verifica_Cpf(vet_clientes, cepefe, cont_clientes);
    if(!pos)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
    pos--;

    if(vet_clientes[pos].status == 1)
    {
        printf("ERRO: Cliente com contrato existente\n");
        return;
    }

    do
    {
        //verificando o tipo de plano :)
        scanf(" %d", &bonito);
        if(bonito == 0 || bonito == 1)
        {
            break;
        }
        else
        {
            printf("ERRO: Tipo de plano invalido\n");
        }
    } while (1);

    vet_contratos[pos].plano_contratado = bonito;

    do
    {
        //verificando o pagamento :)
        scanf(" %d", &bonito);
        if(bonito == 0 || bonito == 1)
        {
            break;
        }
        else
        {
            printf("ERRO: Tipo de pagamento invalido\n");
        }
    } while (1);

    //bonito pra debito ou credito
    if(bonito == 0)
    {
        scanf(" %d", &vet_contratos[pos].pagamento.debito.numero_agencia);
        scanf(" %d", &vet_contratos[pos].pagamento.debito.numero_conta);
    }
    else
    {
        scanf(" %d", &vet_contratos[pos].pagamento.num_cartao);
    }
    
    do
    {
        //verificando o dia :)
        scanf(" %d", &bonito);
        if(bonito >= 1 && bonito <= 31)
        {
            vet_contratos[pos].dia_contrat = bonito;
            vet_contratos[pos].mes_contrat = mes_atual;
            vet_contratos[pos].dia_cancel = 0;
            vet_contratos[pos].mes_cancel = 0;
            vet_clientes[pos].status = 1;
            (*cont_contratos)++;
            printf("Contrato cadastrado com sucesso\n");
            return;
        }
        else
        {
            printf("ERRO: Dia invalido\n");
        }
    } while (1);
}

void Carregar_Filme(HISTORICO mat_historico[][30], CLIENTE *vet_clientes, CONTRATO *vet_contratos, OPLANOB *vet_planos, FILME *vet_filmes, int *vet_cont_assistidos, int cont_clientes, int cont_filmes, int mes_atual, int *vet_cont_exced)
{
    int cepefe, pos, bonito, firme, dia, pesq;

    if(cont_clientes==0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }

    //validar cpf inserido
    scanf(" %d", &cepefe);
    pos = Verifica_Cpf(vet_clientes, cepefe, cont_clientes);
    if(!pos)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
    pos--;

    //verficar se cliente esta ativo
    if(vet_clientes[pos].status == 0)
    {
        printf("ERRO: Cliente nao ativo\n");
        return;
    }

    if(vet_cont_assistidos[pos] == 30)
    {
        printf("ERRO: Numero maximo de filmes no sistema atingido\n");
        return;
    }
    
    //validar dia inserido
    do
    {
        scanf(" %d", &dia);
        if(dia<1 || dia>31)
        {
            printf("ERRO: Dia invalido\n");
        }
        else
        {
            break;
        }
    } while (1);


    //verificar a pesquisa por gen ou class
    do
    {
        scanf(" %d", &pesq);
        if(pesq<0 || pesq>1)
        {
            printf("ERRO: Escolha invalida\n");
        }
        else
        {
            break;
        }
    } while (1);

    //especifica o gen ou class
    do
    {
        scanf(" %d", &bonito);
        if(bonito >= 0 && bonito <= 5)
        {
            break;
        }
        else
        {
            printf("ERRO: Escolha invalida\n");
        }
    } while (1);

    if(pesq==0)
    {
        for(int i=0; i<cont_filmes; i++)
        {
            if(vet_filmes[i].genero == bonito)
            {
                printf("Codigo: %d\n",  vet_filmes[i].cod_chave);
                printf("Nome: %s\n",    vet_filmes[i].nome);
            }
        }
    }
    else
    {
        for(int i=0; i<cont_filmes; i++)
        {
            if(vet_filmes[i].class_indic == bonito)
            {
                printf("Codigo: %d\n",  vet_filmes[i].cod_chave);
                printf("Nome: %s\n",    vet_filmes[i].nome);
            }
        }
    }

    //verificar escolha do filme
    scanf(" %d", &firme);
    if(firme<vet_filmes[0].cod_chave || firme>vet_filmes[cont_filmes-1].cod_chave)
    {
        printf("ERRO: Filme nao encontrado\n"); //n ta dentro D:
        return;
    }
    //ele ta dentro do limite :D
    

    //caso o cliente for premium B)

    if(vet_contratos[pos].plano_contratado == BASICO)
    {

        //caso o cliente for feio :(
        if(vet_cont_assistidos[pos] >= vet_planos[BASICO].qtd_filmes)
        {
            //quer exceder o plano s ou n?
            do
            {
                scanf(" %d", &bonito);
                if(bonito  == 0 || bonito == 1)
                {
                    break;
                }
                else
                {
                    printf("ERRO: Escolha invalida\n");
                }
            } while (1);

            if(bonito == 0)
            {
                printf("ERRO: Taxa adicional negada\n");
                return;
            }
            else if(bonito == 1)
            {
                vet_cont_exced[pos]++;
            }      
        }
    }

    //add filme na matriz e da mensagem de filme foda
    mat_historico[pos][vet_cont_assistidos[pos]].cod_filme.cod_chave = firme;
    mat_historico[pos][vet_cont_assistidos[pos]].dia_assist = dia;
    mat_historico[pos][vet_cont_assistidos[pos]].mes_assist = mes_atual;
    vet_cont_assistidos[pos]++;
    printf("Filme carregado com sucesso\n");
    return;
}

void Cancel_Contrato(CONTRATO *vet_contratos, CLIENTE *vet_clientes, OPLANOB *vet_planos, int *cont_contratos, int cont_clientes, int mes_atual, int *vet_cont_exced)
{
    int pos, cepefe, dia;

    //verificar qtd contratos
    if(*cont_contratos == 0)
    {
        printf("ERRO: Nenhum contrato cadastrado no sistema\n");
        return;
    }

    //verificar cpf inserido
    scanf(" %d", &cepefe);
    pos = Verifica_Cpf(vet_clientes, cepefe, cont_clientes);
    if(!pos)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
    pos--;

    //verificar status cliente
    if(vet_clientes[pos].status == 0)
    {
        printf("ERRO: Cliente inativo\n");
        return;
    }

    //validar dia inserido
    do
    {
        scanf(" %d", &dia);
        if(dia<1 && dia>31)
        {
            printf("ERRO: Dia invalido\n");
        }
        else
        {
            if(dia < vet_contratos[pos].dia_contrat && mes_atual <= vet_contratos[pos].mes_contrat)
            {
                printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
                return;
            }
            if(dia > vet_contratos[pos].dia_contrat && mes_atual < vet_contratos[pos].mes_contrat)
            {
                printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
                return;
            }

            break;
        }
    } while (1);

    if(vet_contratos[pos].plano_contratado == PREMIUM)
    {
        vet_contratos[pos].dia_cancel = dia;
        vet_contratos[pos].mes_cancel = mes_atual;
        vet_clientes[pos].status = 0;
        printf("Valor devido: %.2f\n",vet_planos[1].val_base_plano);
        printf("Cancelamento feito com sucesso\n");
    }
    else if(vet_contratos[pos].plano_contratado == BASICO)
    {
        vet_contratos[pos].dia_cancel = dia;
        vet_contratos[pos].mes_cancel = mes_atual;
        vet_clientes[pos].status = 0;
        printf("Valor devido: %.2f\n",vet_planos[0].val_base_plano + (vet_planos[0].val_exced * vet_cont_exced[pos]));
        printf("Cancelamento feito com sucesso\n");
    }
    (*cont_contratos)--;
    return;
}

void Gerar_Fatura(FILME *vet_filmes, int cont_filmes, HISTORICO mat_historico[][30], int *vet_cont_assistidos, CONTRATO *vet_contratos, CLIENTE *vet_clientes, OPLANOB *vet_planos, int cont_contratos, int cont_clientes, int *mes_atual, int *vet_cont_exced)
{
    int cepefe, bonito, pos;

    //0 ou 1
    do
    {
        scanf(" %d", &bonito);
        if(bonito == 0 || bonito == 1)
        {
            break;
        }
        else 
        {
            printf("ERRO: Escolha invalida\n");
        }
    } while (1);
    
    if(bonito == 0)
    {
        //tem contrato s ou n?
        if(cont_clientes == 0)
        {
            printf("ERRO: Nenhum cliente cadastrado no sistema\n");
            return;
        }

        //cpf existe?
        scanf(" %d", &cepefe);
        pos = Verifica_Cpf(vet_clientes, cepefe, cont_clientes);
        if(!pos)
        {
            printf("ERRO: Cliente nao cadastrado\n");
            return;
        }
        pos--;

        //tem contrato?
        if(vet_clientes[pos].status == 0)
        {
            printf("ERRO: Cliente nao possui contrato\n");
        }

        //qual plano
        //0 basico 1 premium
        if(vet_contratos[pos].plano_contratado == BASICO)
        {
            for(int i=0; i<vet_cont_assistidos[pos]; i++)
            {
                for(int j=0; j<cont_filmes; j++)
                {
                    if(mat_historico[pos][i].cod_filme.cod_chave == vet_filmes[j].cod_chave)
                    {
                        printf("Nome: %s\n", vet_filmes[j].nome); //nome do filme
                        printf("Data: %d/%d\n", mat_historico[pos][i].dia_assist, mat_historico[pos][i].mes_assist); //data do carregamento
                    }
                }
            }
            printf("Valor devido: %.2f\n", vet_planos[0].val_base_plano + (vet_cont_exced[pos] * vet_planos[0].val_exced));
        }
        else if(vet_contratos[pos].plano_contratado == PREMIUM)
        {
            for(int i=0; i<vet_cont_assistidos[pos]; i++)
            {
                for(int j=0; j<cont_filmes; j++)
                {
                    if(mat_historico[pos][i].cod_filme.cod_chave == vet_filmes[j].cod_chave)
                    {
                        printf("Nome: %s\n", vet_filmes[j].nome); //nome do filme
                        printf("Data: %d/%d\n", mat_historico[pos][i].dia_assist, mat_historico[pos][i].mes_assist); //data do carregamento
                    }
                }
            }
            printf("Valor devido: %.2f\n", vet_planos[1].val_base_plano);
        }   
    }
    else
    {
        for(int i=0; i<cont_clientes; i++)
        {
            if(vet_clientes[i].status == 1)
            {
                if(vet_contratos[i].plano_contratado == BASICO)
                {
                    printf("CPF: %d\n", vet_clientes[i].cpf);
                    printf("Nome: %s\n", vet_clientes[i].nome); //nome do cliente
                    printf("Valor devido: %.2f\n", vet_planos[0].val_base_plano + (vet_planos[0].val_exced * vet_cont_exced[i]));
                }
                else if(vet_contratos[i].plano_contratado == PREMIUM)
                {
                    printf("CPF: %d\n", vet_clientes[i].cpf);
                    printf("Nome: %s\n", vet_clientes[i].nome); //nome do cliente
                    printf("Valor devido: %.2f\n", vet_planos[1].val_base_plano);
                }
            }
        }

        //zerar tudo
        for(int i=0; i<10; i++)
        {
            for(int j=0; j<30; j++)
            {
                mat_historico[i][j].cod_filme.cod_chave=0;
                mat_historico[i][j].dia_assist=0;
                mat_historico[i][j].mes_assist=0;
            }
            vet_cont_assistidos[i]=0;
            vet_cont_exced[i]=0;
        }
    
        (*mes_atual)++;
        printf("Mes vigente apos a fatura: %d\n", *mes_atual);
    }
    return;
}

void Listar_Dados_Cliente(CLIENTE *vet_clientes, int cont_clientes)
{
    int cepefe, pos;

    if(cont_clientes==0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    scanf(" %d", &cepefe);
    pos = Verifica_Cpf(vet_clientes, cepefe, cont_clientes);

    if(!pos)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
    pos--;
    printf("Nome: %s\n", vet_clientes[pos].nome);
    printf("Email: %s\n", vet_clientes[pos].email);
    printf("Telefone: %s\n", vet_clientes[pos].telefone);
    printf("Status: %d\n", vet_clientes[pos].status);
}

void Listar_Historico(CLIENTE *vet_clientes, int cont_clientes, FILME *vet_filmes, int cont_filmes, HISTORICO mat_historico[][30], int *vet_cont_assistidos)
{
    int cepefe, pos;

    if(cont_clientes == 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }

    scanf(" %d", &cepefe);
    pos = Verifica_Cpf(vet_clientes, cepefe, cont_clientes);
    if(!pos)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
    pos--;

    if(vet_clientes[pos].status == 1)
    {
        printf("Estado: Ativo\n");
    }
    else if(vet_clientes[pos].status == 0)
    {
        printf("Estado: Inativo\n");
    }   
    if(vet_cont_assistidos[pos] == 0)
    {
        printf("ERRO: Nenhum filme assistido\n");
        return;
    }
    for(int i=0; i<vet_cont_assistidos[pos]; i++)
    {
        printf("Codigo: %d\n",mat_historico[pos][i].cod_filme.cod_chave); //codigo do filme
        for(int j=0; j<cont_filmes; j++)
        {
            if(mat_historico[pos][i].cod_filme.cod_chave == vet_filmes[j].cod_chave)
            {
                printf("Nome: %s\n", vet_filmes[j].nome); //nome do filme

                if(vet_filmes[j].genero == 0)
                {
                    printf("Genero: aventura\n"); //escrito por extenso (exemplo: aventura, comedia, ...)
                }
                else if(vet_filmes[j].genero == 1)
                {
                    printf("Genero: comedia\n"); //escrito por extenso (exemplo: aventura, comedia, ...)
                }
                else if(vet_filmes[j].genero == 2)
                {
                    printf("Genero: drama\n"); //escrito por extenso (exemplo: aventura, comedia, ...)
                }
                else if(vet_filmes[j].genero == 3)
                {
                    printf("Genero: terror\n"); //escrito por extenso (exemplo: aventura, comedia, ...)
                }
                else if(vet_filmes[j].genero == 4)
                {
                    printf("Genero: acao\n"); //escrito por extenso (exemplo: aventura, comedia, ...)
                }
                else
                {
                    printf("Genero: romance\n"); //escrito por extenso (exemplo: aventura, comedia, ...)
                }

                if(vet_filmes[j].class_indic == 0)
                {
                    printf("Classificacao: livre\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                }
                else if(vet_filmes[j].class_indic == 1)
                {
                    printf("Classificacao: +10\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                }
                else if(vet_filmes[j].class_indic == 2)
                {
                    printf("Classificacao: +12\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                }
                else if(vet_filmes[j].class_indic == 3)
                {
                    printf("Classificacao: +14\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                }
                else if(vet_filmes[j].class_indic == 4)
                {
                    printf("Classificacao: +16\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                }
                else
                {
                    printf("Classificacao: +18\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                }
            }
        }
        printf("Data do carregamento: %d/%d\n\n",mat_historico[pos][i].dia_assist, mat_historico[pos][i].mes_assist);
    }
}

void Listar_Cliente_Exced(OPLANOB *vet_planos, CLIENTE *vet_clientes, int cont_clientes, int *vet_cont_exced)
{
    int ok=0;

    for(int i=0; i<cont_clientes; i++)
    {
        if(vet_cont_exced[i] > 0)
        {
            printf("CPF: %d\n", vet_clientes[i].cpf);
            printf("Nome: %s\n", vet_clientes[i].nome);
            printf("Valor excedente: %.2f\n\n", vet_planos[0].val_exced * vet_cont_exced[i]);
            ok=1;
        }
    }

    if(ok==0)
    {
        printf("ERRO: Nenhum cliente excedente\n");
        return;
    }
}

void Frequencia_Filme(HISTORICO mat_historico[][30], FILME *vet_filmes, int cont_filmes, int *vet_cont_assistidos)
{
    int cod_firme;
    int ok=0;
    float cont_total=0, cont_espec=0;

    if(cont_filmes == 0)
    {
        printf("ERRO: Nenhum filme cadastrado no sistema\n");
        return;
    }

    //validar codigo do filme inserido
    scanf(" %d", &cod_firme);
    for(int i=0; i<cont_filmes; i++)
    {
        if(cod_firme == vet_filmes[i].cod_chave)
        {
            ok=1;
        }
    }
    if(ok==0)
    {
        printf("ERRO: Codigo invalido\n");
        return;
    }

    for(int i=0; i<10; i++)
    {
        cont_total += vet_cont_assistidos[i];

        for(int j=0; j<30; j++)
        {
            if(mat_historico[i][j].cod_filme.cod_chave == cod_firme)
            {
                cont_espec++;
            }
        }
    }

    printf("Frequencia: %.2f%%\n", (cont_espec/cont_total) * 100);
}

void Recomendar_Filme(HISTORICO mat_historico[][30], FILME *vet_filmes, int cont_filmes, int *vet_cont_assistidos, CLIENTE *vet_clientes, int cont_clientes)
{
    int cepefe, pos;

    if(cont_clientes == 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }

    scanf(" %d", &cepefe);
    pos = Verifica_Cpf(vet_clientes, cepefe, cont_clientes);
    if(!pos)
    {
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
    pos--;

    if(vet_clientes[pos].status == 0)
    {
        printf("ERRO: Cliente nao ativo\n");
        return;
    }

    if(vet_cont_assistidos[pos] == 0)
    {
        printf("ERRO: Nenhum filme assistido\n");
        return;
    }
}
# PRINCIPAL
pastas = ['processo', 'thread']
#pastas = ['processo', 'thread']
dimensoes = ['2', '4', '6', '16', '24', '32']

# FUNCAO PARA FORMATAR E ESCREVER OS TEMPOS
def escrever_tempos(arquivo, arq_saida):
    arq = open(arquivo)
    linhas = arq.readlines()
    arq_saida.write(linhas[-1][7:] + "\n")

# INICIO DO PROCESSO
for pasta in pastas:
    for dim in dimensoes:
        nome_arquivo = 'experimento-02/arquivos-' + pasta + '/' + pasta + '_tempos_' + dim + '.txt' 
        arq_saida = open(nome_arquivo, "a")

        print("COMEÇOU " + dim + " na pasta " + pasta + "! ")
        caminho = 'experimento-02/arquivos-' + pasta  + '/' +  dim
        for i in range(1,11):            
            maior = 0
            for j in range(0,int(dim)):
                arquivo = caminho + '/' + str(i) + '/matriz_' + pasta + 's' + str(j) + '.txt'
                arq = open(arquivo)
                linhas = arq.readlines()
                if(int(linhas[-1][7:]) > int(maior)):
                    maior = linhas[-1][7:]
                if(j == 7):
                    arq_saida.write(maior + "\n")
            
                    
            
            

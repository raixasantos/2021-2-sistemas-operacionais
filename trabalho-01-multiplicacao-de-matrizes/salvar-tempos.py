# PRINCIPAL
pastas = ['processo', 'thread', 'sequencial']
#pastas = ['processo', 'thread']
dimensoes = ['100x100', '200x200', '400x400', '800x800', '1600x1600', '3200x3200']

# FUNCAO PARA FORMATAR E ESCREVER OS TEMPOS
def escrever_tempos(arquivo, arq_saida):
    arq = open(arquivo)
    linhas = arq.readlines()
    arq_saida.write(linhas[-1][7:] + "\n")

# INICIO DO PROCESSO
for pasta in pastas:
    for dim in dimensoes:
        nome_arquivo = 'arquivos-' + pasta + '/' + pasta + '_tempos_' + dim + '.txt' 
        arq_saida = open(nome_arquivo, "a")

        # print("COMEÇOU " + dim + " na pasta " + pasta + "! ")
        caminho = 'arquivos-' + pasta  + '/' +  dim
        for i in range(1,11):            
            if(pasta == 'sequencial'):
                arquivo = caminho + '/' + str(i) + '/matriz_' + pasta + '.txt'
                escrever_tempos(arquivo, arq_saida)
            
            else:
                maior = 0
                for j in range(0,8):
                    arquivo = caminho + '/' + str(i) + '/matriz_' + pasta + 's' + str(j) + '.txt'
                    arq = open(arquivo)
                    linhas = arq.readlines()
                    if(int(linhas[-1][7:]) > int(maior)):
                        maior = linhas[-1][7:]
                    if(j == 7):
                        arq_saida.write(maior + "\n")
                    
            
            

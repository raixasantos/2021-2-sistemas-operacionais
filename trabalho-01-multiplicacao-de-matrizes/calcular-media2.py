# PRINCIPAL
pastas = ['processo', 'thread']
dimensoes = ['2', '4', '6', '8','16', '24', '32']


# INICIO DO PROCESSO
arq_saida = open("medias_das_multiplicacoes.txt", "a")
for pasta in pastas:
    #print(pasta + ":")
    for dim in dimensoes:
        nome_arquivo = 'experimento-02/arquivos-' + pasta + '/' + pasta + '_tempos_' + dim + '.txt' 
        #print(dim)
        arq = open(nome_arquivo)
        linhas = arq.readlines()
        media = 0
        for i in range(0, len(linhas)):
            media += int(linhas[i])
        media_final = media/10
        arq_saida.write(dim + ' ' + str(media_final) + "\n")
        print(media/10)
    print()
    arq_saida.write("\n")

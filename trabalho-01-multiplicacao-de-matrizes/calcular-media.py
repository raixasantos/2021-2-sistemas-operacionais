# PRINCIPAL
pastas = ['sequencial', 'processo', 'thread']
dimensoes = ['100x100', '200x200', '400x400', '800x800', '1600x1600', '3200x3200']


# INICIO DO PROCESSO
arq_saida = open("medias_das_multiplicacoes.txt", "a")
for pasta in pastas:
    #print(pasta + ":")
    for dim in dimensoes:
        nome_arquivo = 'arquivos-' + pasta + '/' + pasta + '_tempos_' + dim + '.txt' 
        #print(dim)
        arq = open(nome_arquivo)
        linhas = arq.readlines()
        media = 0
        for i in range(0, len(linhas)):
            media += int(linhas[i])
        media_final = media/10
        arq_saida.write(str(media_final) + "\n")
        print(media/10)
    print()

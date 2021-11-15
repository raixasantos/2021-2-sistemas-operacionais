# PRINCIPAL
pastas = ['processo', 'sequencial', 'thread']
dimensoes = ['100x100', '200x200', '400x400', '800x800', '1600x1600', '3200x3200']


# INICIO DO PROCESSO
for pasta in pastas:
    for dim in dimensoes:
        nome_arquivo = 'arquivos-' + pasta + '/' + pasta + '_tempos_' + dim + '.txt' 

        arq = open(nome_arquivo)
        linhas = arq.readlines()
        print(len(linhas))
    print()

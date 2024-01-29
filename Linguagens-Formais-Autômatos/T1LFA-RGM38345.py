#Lucas da Rocha Silva 38345

#criando uma lista e dicionarios vazios
transicao = dict()
conjTransicao = list()

op = 'S'
logica = False
valida = False
cont = 0

#loop para ver se o usuario quer continuar no programa
while(op == 'S' or op == 's'):

    estados = input('informe os conjuntos de estados (obs: tudo junto):')

    #loop para pegar um estado inicial valido 
    while logica == False:

        estIni = input('informe um estado inicial valido (obs: tudo junto):')

        for i in estados:

            if estIni == i and len(estIni) == 1:
                logica = True
                break
    
    logica = False

    estFinal = input('informe um conjunto de estados finais validos (obs: tudo junto):')
    
    alfab = input('informe o alfabeto (obs: tudo junto):')

    #percorrendo cada estado com cada alfabeto para fornecer o estado destino
    for i in estados:

        for j in alfab:

            transicao['origem'] = i
            transicao['caminho'] = j
            
            #loop para o usuario fornecer um destino valido
            while logica == False:

                destino = input('D({}, {}):'. format(i,j))

                for k in estados:

                    if destino == k:
                        logica = True
                        break

            logica = False
            transicao['dest'] = destino

            #colocando a transicao na lista de conjunto de transicoes
            conjTransicao.append(transicao.copy())

    palavra = input('entre com a palavra:')

    estadoAtual = estIni
    seq = estIni

    #loops para verificar os caminhos percorridos pela palavra fornecida
    for k in palavra:

        for i in conjTransicao:  

            if estadoAtual == i['origem']:
                #aqui vai armazenar cada estado de transicao
                if i['caminho'] == k:
                    estadoAtual = i['dest']
                    seq += estadoAtual
                    break

    print('sequencia de estados:')             
    print(seq)

    #pega o ultimo estado
    final = seq[len(seq) - 1]

    #compara se satisfaz o estado final
    if final in estFinal:
        print('palavra valida!!')

    else:
        print('palavra nao é valida!!')

    op = input('deseja continuar S/N:')
<body>
    <h1>Sistema Bancário QuemPoupaTem</h1>
    <p>Basicamente um Programa simples, desenvolvido em C, que é um Sistema Bancario </p>
<body>
    <h2>Objetivo</h2>
    <p>O objetivo do programa desenvolvido é gerenciar contas bancárias de clientes, permitindo a realização de operações básicas como criação de contas, depósitos, saques, transferências e emissão de extratos.</p>
<body>
    <h2>Requisitos</h2>
    <p>O sistema trabalha com dois tipos de conta:</p>
    <ul>
        <li><strong>Comum:</strong> Cobra taxa de 5% a cada débito realizado. Permite saldo negativo de até R$ 1.000,00.</li>
        <li><strong>Plus:</strong> Cobra taxa de 3% a cada débito realizado. Permite saldo negativo de até R$ 5.000,00.</li>
    </ul>
    <p>O sistema deve funcionar em loop infinito até que se deseje sair, apresentando um menu de opções ao operador.</p>
<body>
    <h2>Menu de Opções</h2>
    <p>O menu de opções contém as seguintes operações abaixo:</p>
 <ol>
        <li>Novo cliente</li>
        <li>Apaga cliente</li>
        <li>Listar clientes</li>
        <li>Débito</li>
        <li>Depósito</li>
        <li>Extrato</li>
        <li>Transferência Entre Contas</li>
        <li>Sair</li>
    </ol>
<body>
    <h2>Funcionalidades</h2>
    <h3>1. Novo cliente</h3>
    <p>Esta função é usada para criar novos clientes. Solicita os seguintes dados:</p>
    <ul>
        <li>Nome</li>
        <li>CPF</li>
        <li>Tipo de conta (Comum ou Plus)</li>
        <li>Valor inicial da conta</li>
        <li>Senha do usuário</li>
    </ul>
<body>
    <h3>2. Apaga cliente</h3>
    <p>Apaga o cliente pelo CPF. Esta função remove o cliente do sistema, liberando espaço para novos clientes.</p>
<body>
    <h3>3. Listar clientes</h3>
    <p>Lista todos os clientes cadastrados no sistema, exibindo suas informações básicas.</p>
<body>
    <h3>4. Débito</h3>
    <p>Realiza o débito de um valor na conta do cliente. Solicita os seguintes dados:</p>
    <ul>
        <li>CPF</li>
        <li>Senha</li>
        <li>Valor</li>
    </ul>
    <p>O débito só pode ser realizado se o CPF e a senha estiverem corretos. Aplica a taxa correspondente ao tipo de conta.</p>
<body>
    <h3>5. Depósito</h3>
    <p>Realiza o depósito de um valor na conta do cliente. Solicita o CPF e o valor do depósito.</p>
<body>
    <h3>6. Extrato</h3>
    <p>Gera um extrato com o histórico de todas as operações realizadas na conta, incluindo valores e tarifas. Solicita os seguintes dados:</p>
    <ul>
        <li>CPF</li>
        <li>Senha</li>
    </ul>
    <p>O extrato é gerado em formato TXT e pode ser aberto em qualquer editor de texto.</p>
<body>
    <h3>7. Transferência Entre Contas</h3>
    <p>Realiza a transferência de um valor determinado de uma conta (Origem) para outra conta (Destino). Solicita os seguintes dados:</p>
    <ul>
        <li>CPF (Origem)</li>
        <li>Senha (Origem)</li>
        <li>CPF (Destino)</li>
        <li>Valor</li>
    </ul>
    <p>A transferência só pode ser realizada se o CPF e a senha da conta de origem estiverem corretos.</p>
<body>
    <h2>Armazenamento de Dados</h2>
    <p>Todos os dados dos clientes e operações são armazenados de maneira permanente utilizando arquivos binários. Isso garante que as informações não sejam perdidas mesmo que o programa seja encerrado ou o computador desligado.</p>

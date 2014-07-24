Recuperação de Seed - Vulnerabilidade urna brasileira
=====================================================

Este repositório é parte do projeto de pós-graduação do estudante Bruno de Souza Lobo Almeida no curso de Perícia Forense Aplicada à Informática pela Faculdade Integrada AVM.

Seu uso é destinado unicamente à pesquisa e baseia-se no capítulo "Software vulnerabilities in the Brazilian voting machine" escritos por Diego F. Aranha, Marcelo Monte Karam, André de Miranda e Felipe Scarel do livro "Design, Development, and Use of Secure Electronic Voting Systems".


DataBase
========
Por se tratar de um banco de dados orientado a arquivos (JSON) a estrutura do banco de dados foi criada da seguinte forma:

{
  name: nome_do_candidato, (String)
  party: partido_do_candidato (int)
  number: numero_do_candidato (int)
}

Foi escolido este banco de dados para facilitar a serialização e envio das informações pelo web-service.

Instalação
----------

Para recuperar este backup basta executar o seguinte comando, com o mongodb não iniciado:

~~~ sh
$mongorestore --dbpath "path" path_to/database/mongo-backup
~~~
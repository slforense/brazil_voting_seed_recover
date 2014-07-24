Recuperação de Seed - Vulnerabilidade urna brasileira
=====================================================

Este repositório é parte do projeto de pós-graduação do estudante Bruno de Souza Lobo Almeida no curso de Perícia Forense Aplicada à Informática pela Faculdade Integrada AVM.

Seu uso é destinado unicamente à pesquisa e baseia-se no capítulo "Software vulnerabilities in the Brazilian voting machine" escritos por Diego F. Aranha, Marcelo Monte Karam, André de Miranda e Felipe Scarel do livro "Design, Development, and Use of Secure Electronic Voting Systems".


O Projeto
========================
O projeto é divido em 5 partes:

* O Banco de Dados (Armazena os candidatos)
  * Mongodb - http://www.mongodb.org/
  
* O Web-Service (Ponto de recuperação dos candidatos)
  * NodeJS - http://nodejs.org/
  * Hapi - http://hapijs.com/
  * Mongoose - http://mongoosejs.com/
  
* A simulação da Urna
  * Qt / C++ - qt-project.org
  
* A ferramenta de recuperação de votos
  * Qt / C++ - qt-project.org
  
* Uma rotina de população automática (dados aleatórios) do banco de dados
  * Java - java.com
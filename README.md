# RiverINF
Projeto de raylib para fazer um jogo - Cauã e Negretto

- Próxima etapa: ver se consigo incluir headers (e como fazer headers) no meu launch.json ou tasks.json, 
assim, posso aproveitar o makefile do raylib, que já é completinho.

- se feito da maneira correta, tende a ser fácil.

# Sobre o jogo:

- Sem muita enrolação, é uma cópia barata do jogo RiverRaid, com um código bem escrito e de fácil manipulção, quer adicionar algo? Provavelmente basta adicionar algo em definicoes.h e sua chamada de funcao - ou uma nova função - em logicaprincipal.c.

- Definitivamente foi interessante, todo o projeto, e tem muitas melhorias e ideias que surgem na cabeça quando deixamos o código menos chato de mexer

- Grande parte do tempo foi recodificando a maçaroca que mal funcionava antes, depois, foi muito mais modularizado e organizado

- O código já é tooodo comentado, então não há necessidade de muita descrição além disso.

- Evidentemente, o jogo é programado em 3 modulos auxiliares, cada um com seu header, +1 header adicional, e o main.c, aqui batizado de RiverINF.c

- RiverINF.c: geralmente chamado de main.c, é onde fica o loop principal do jogo, em desenho e lógica mesmo, chamando funções de logicaprincipal.c, ranking.c e recursos.c

- logicaprincipal.c: definitivamente o segundo no comando aqui, sem ele nada funciona e nem fica perto de funcionar, funções primitivas de atualizacao do jogo e tudo sobre o mapa residem aqui.

- ranking.c: separamos porque criamos num momento onde já estavamos preocupados com a organização

- recursos.c: literalmente é só carregar e descarregar todas as texturas e sons do jogo, achamos melhor separar porque fica muito mais facil modificar o jogo assim.

headers:
- Os 3 com nome igual aos arquivos.c é só por segurança e boa prática
- definicoes.h: para nao lotar RiverINF.c com coisa chata e deixar ele um pouco menos poluido, usamos essa header só para definir - evidente - a maioria dos pontos decisivos e auxiliares que facilitam controle de frames de desenho como em explosao e tempo de vida como nos projeteis

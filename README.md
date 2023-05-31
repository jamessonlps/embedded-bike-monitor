# 21b - APS2 - Embarcados

O marketing de uma empresa de equipamentos esportivos quer criar um novo ciclocomputador e você foi escolhido como desenvolvedor autônomo, dado seu background técnico e de UX, para criar um protótipo e validar a ideia.

Mais detalhes no site da disciplina:

- https://insper.github.io/ComputacaoEmbarcada/navigation/APS/APS-2-Bike/Descricao/

## Detalhes

Integrantes:

- **Ivan de Alcântara Barbosa Barros**
- **Jamesson Leandro Paiva Santos**

## Marca

**EVEREST**
<img src="/img/logo.png" alt="Everest logo"/>

## Interface

### Proposta UX 1 - C

A nossa primeira ideia consiste em 6 telas. A primeira é a tela de configurações iniciais, a segunda é a tela em que há um botão para iniciar a corrida. A terceira tela é a tela principal, que mostra em tempo real os dados da pedalada. A ênfase maior fica com a velocidade instantânea, seguida de outras como tempo, distância, calorias e altitude, e depois as velocidades média e máxima do percurso. O ciclista pode pausar o processo ou finalizar por meio de botões em baixo. Ao finalizar, é levado para as últimas 3 telas, que mostram as principais informações odo percurso e 2 gráficos (altitude _vs_ tempo e velocidade _vs_ tempo).

Os widgets utilizados estão especificados no [mural](https://app.mural.co/t/elementos9119/m/elementos9119/1652116252461/f773497a764ead5f57048cedf89780811768c460?sender=ub569a9273c6e285461187641).

<img src="/img/mockup1.png" alt="mockup 1"/>

Veja esse [vídeo](https://youtu.be/_uJFW_GbpE4) sobre o nosso primeiro design.

Imagem estática da tela principal no LCD:

<img src="/img/lcdv1.jpg" alt="lcd 1" />

### Proposta UX 2 - B

Após a nossa primeira entrevista, que pode ser assistida [aqui](https://youtu.be/_clOZnBlroI), mudamos:

- Configuração do aro da bicicleta passou a ser via Drop List (por conta de diferentes padrões das bicicletas)
- Adição do botão de configuração na tela inicial
- Mudança da fonte do texto
- Texto na barra superior com **bold** para facilitar visualização.
- Botões de _anterior_ e _próximo_ no resumo.

Quanto à fonte, mudamos para a fonte **Roboto**, que não possui serifa e, portanto, deixa a visualização menos "carregada" e mais intuitiva. Além disso, definimos o tamanho dos textos conforme a relevância daquilo ao ser visto pelo ciclista. Na tela de atividade, a velocidade instantânea tem maior prioridade (tamanho 46 e **bold**), enquantos os demais tem 18 de tamanho. Os textos ficam em tamanho menor (10) para não tirarem o foco da visualização no número. Os demais botões com texto possui tamanho 18 também, euquanto a data e hora na parte superior são mostrados com tamanho 12.

O vídeo com as mudanças feitas encontra-se [aqui](https://youtu.be/FarSkcJUhzo).

<img src="/img/mockup2.png" alt="mockup 2"/>

Tela principal no LCD:

<img src="/img/lcdv2.jpg" alt="lcd 2" />

### Proposta UX 3 - A

Nessa terceira etapa, fizemos algumas mudanças sem ligação direta com a entrevista:

- Adição de tela de entrada (mostra a logo)
- Divide configuração em três partes: Data, hora e bike
- Botões de _configuração_ e _pedalar_ na tela de de corrida com tamanhos iguais.

A entrevista com a pessoa externa pode ser assistida [aqui](https://youtu.be/pN-KivqYxKg).

As mudanças foram:

- Adição do peso da bicicleta nas configurações.
- Mudança da cor dos ícones dos botões na tela de corrida para dar mais constraste e facilitar visualização.
- Redução da expessura dos círculos que mostram as velocidades.
- Adição de _ganho de elevação_ no resumo.
- Adição de _temperatura média_ no resumo.
- Remoção dos gráficos no resumo (para ciclistas profissionais, não parece ser tão útil exbir em um display pequeno que permite poucos detalhes). A ideia é tornar isso exportável via um cartão de memória, por exemplo, para permitir ver gráficos mais detalhados no celular ou no computador.

Fizemos um vídeo mostrando as mudanças que fizemos, cujo link está [aqui](https://youtu.be/appighV4rj8).

<img src="/img/mockup3.png" alt="mockup 3"/>

O nosso dispositivo é voltado para os amantes de ciclismo, que curtem fazer trilhas e longos percursos. Pensando nisso, escolhermos a cor **verde** para a nossa interface, pois essa cor remete à saúde e à natureza, que são elementos bastante presentes para muitos ciclistas que gostam de se aventurar tanto na cidade quanto em trilhas mais afastadas, no meio do mato ou em meio às paisagens verdes e arborizadas dos grandes centros urbanos.

Tela principal no LCD:

<img src="/img/lcdv3.jpg" alt="lcd 3" />

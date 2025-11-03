# 🎮 SO LONG - Roadmap do Projeto

---

## 📦 **FASE 0** — Preparação e organização
**⏱️ Tempo:** 1 dia (5h)  
**🎯 Objetivo:** Ambiente pronto, MinilibX funcionando, Makefile básico

### ✅ Checklist do Dia 1 (5h)

#### 🔧 Bloco 1 (50 min)
- [x] Criar repositório Git
- [x] Adicionar `.gitignore`
- [x] Criar estrutura: `src/`, `include/`, `assets/`, `maps/`, `libs/libft/`
- [x] Escrever README mínimo
- **🎯 Meta:** Repo inicial criado
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "init: project structure"`

#### 🔧 Bloco 2 (50 min)
- [x] Instalar/colocar MinilibX no projeto
- [x] Adicionar ao Makefile: `NAME`, `all`, `clean`, `fclean`, `re`
- [x] Testar compilação (sem relink desnecessário)
- **🎯 Meta:** Makefile compila sem erros
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "build: add minilibx to Makefile"`

#### 🔧 Bloco 3 (50 min)
- [x] Copiar/configurar libft
- [x] Testar flags: `-Wall -Wextra -Werror`
- [x] Garantir que `make` cria binário
- **🎯 Meta:** Binário criado (mesmo vazio)
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "chore: libft scaffold"`

#### 🔧 Bloco 4 (50 min)
- [x] Script de teste básico: `./so_long maps/test.ber`
- [x] Deve mostrar erro amigável se mapa inválido
- [ ] Atualizar README com passos de compilação
- **🎯 Meta:** Teste básico funcionando
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "test: basic run checks"`

### 🏆 **Critério de Aceitação:**
✅ `make` produz binário  
✅ MinilibX linkado  
✅ Repositório pronto para desenvolvimento

---

## 🗺️ **FASE 1** — Parser de mapa e validações
**⏱️ Tempo:** 2–3 dias (recomendado 3 dias)  
**🎯 Objetivo:** Ler `.ber`, validar formato, paredes, caracteres, contagem P/E/C, caminho válido (BFS/DFS)

### ✅ Checklist do Dia 2 (5h) — Leitura + Validações Básicas

#### 📖 Bloco 1 (50 min)
- [ ] Implementar leitura de `.ber` em memória (`char **map`)
- [ ] Usar `while` para percorrer linhas
- **🎯 Meta:** Mapa carregado em memória
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: load map file"`

#### 🔍 Bloco 2 (50 min)
- [ ] Checar retangularidade (todas linhas mesmo tamanho)
- [ ] Validar caracteres: só `0`, `1`, `C`, `E`, `P`
- [ ] Mensagens de erro: `Error\n<mensagem>`
- **🎯 Meta:** Validações básicas funcionando
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: validate characters & rectangle"`

#### 🧱 Bloco 3 (50 min)
- [ ] Checar bordas fechadas:
  - Linha superior = só `1`
  - Linha inferior = só `1`
  - Primeira/última coluna de cada linha = `1`
- **🎯 Meta:** Bordas validadas
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: validate walls"`

#### 🔢 Bloco 4 (50 min)
- [ ] Contar elementos:
  - Exatamente 1 `P` (player)
  - Exatamente 1 `E` (exit)
  - Pelo menos 1 `C` (collectible)
- **🎯 Meta:** Contagem implementada
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: validate counts"`

---

### ✅ Checklist do Dia 3 (5h) — Caminho Válido + Testes

#### 🛤️ Bloco 1 (50 min)
- [ ] Implementar BFS/DFS partindo de `P`
- [ ] Marcar todas células acessíveis
- [ ] Verificar que todos `C` e `E` são alcançáveis
- **🎯 Meta:** Pathfinding validado
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: pathfinding validation"`

#### 🧪 Bloco 2 (50 min)
- [ ] Criar 4–6 mapas de teste em `maps/`:
  - ✅ Mapa válido
  - ❌ Não retangular
  - ❌ Borda aberta
  - ❌ Múltiplos P/E
  - ❌ Sem caminho válido
- **🎯 Meta:** Suite de testes pronta
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "test: add maps for validation"`

#### 🐛 Bloco 3 (50 min)
- [ ] Rodar todos testes
- [ ] Corrigir bugs encontrados
- [ ] Melhorar mensagens de erro
- **🎯 Meta:** Todos mapas respondem corretamente
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "fix: validation bug fixes"`

#### 📝 Bloco 4 (50 min)
- [ ] Limpar código
- [ ] Adicionar comentários explicativos
- [ ] Revisar checklist
- **🎯 Meta:** Fase documentada
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "docs: map validation comments"`

### 🏆 **Critério de Aceitação:**
✅ `./so_long maps/valid.ber` → prossegue  
✅ `maps/invalid_*.ber` → retorna `Error\n<mensagem>`  
✅ BFS garante caminho válido

---

## 🎨 **FASE 2** — Renderização do mapa & texturas
**⏱️ Tempo:** 2 dias  
**🎯 Objetivo:** Desenhar mapa com tiles, carregar sprites via MinilibX, mostrar Louis & Ozzy 🐱

### ✅ Checklist do Dia 4 (5h) — Carregar Imagens + Desenho Básico

#### 🖼️ Bloco 1 (50 min)
- [ ] Criar função `load_texture(path)`
- [ ] Carregar XPM/PNG compatíveis com MinilibX
- [ ] Texturas para: parede, chão, coletável, saída, player
- **🎯 Meta:** Texturas carregadas
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: texture loader"`

#### 🗺️ Bloco 2 (50 min)
- [ ] Definir tile size (ex: 64x64)
- [ ] Draw loop para renderizar matriz na janela
- [ ] Testar com mapa pequeno
- **🎯 Meta:** Mapa renderizado em escala
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: render map tiles"`

#### 🐱 Bloco 3 (50 min)
- [ ] Substituir placeholders por sprites dos gatos
- [ ] Louis (player) visível
- [ ] Ozzy (enemy) visível
- [ ] (Se sprites não prontos, usar provisórios)
- **🎯 Meta:** Louis e Ozzy aparecem no mapa
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: add player & enemy sprites"`

#### 🪟 Bloco 4 (50 min)
- [ ] Garantir janela responsiva
- [ ] ESC fecha janela
- [ ] Botão X fecha janela
- [ ] Limpeza correta na saída
- **🎯 Meta:** Controles de janela funcionando
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "chore: window controls"`

---

### ✅ Checklist do Dia 5 (5h) — Otimizações + Contador

#### ✨ Bloco 1 (50 min)
- [ ] Desenhar coletáveis (`C`)
- [ ] Desenhar saída (`E`)
- [ ] Testar com diferentes mapas
- **🎯 Meta:** Todos elementos visíveis
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: draw collectibles & exit"`

#### 🔢 Bloco 2 (50 min)
- [ ] Implementar contador de movimentos (começa em 0)
- [ ] Imprimir no terminal a cada movimento
- [ ] Formato: `Moves: X`
- **🎯 Meta:** Contador funciona
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: move counter"`

#### 🧹 Bloco 3 (50 min)
- [ ] Funções para liberar imagens
- [ ] Liberar memória alocada
- [ ] Testar `make fclean`
- [ ] (Ideal: rodar valgrind)
- **🎯 Meta:** Sem leaks básicos
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "chore: free resources"`

#### 🐛 Bloco 4 (50 min)
- [ ] Testes finais com mapas variados
- [ ] Corrigir bugs visuais
- [ ] Ajustar renderização
- **🎯 Meta:** Renderização estável
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "test: visual fixes"`

### 🏆 **Critério de Aceitação:**
✅ Mapa desenhado corretamente  
✅ Sprites visíveis (Louis, Ozzy, coletáveis, saída)  
✅ ESC e X fecham janela  
✅ Contador de movimentos impresso no terminal

---

## 🕹️ **FASE 3** — Movimento do jogador e colisões
**⏱️ Tempo:** 2 dias  
**🎯 Objetivo:** Louis se move (WASD/ZQSD), colide com paredes, coleta itens, sai quando pegar tudo

### ✅ Checklist do Dia 6 (5h) — Movimento + Coleta

#### ⌨️ Bloco 1 (50 min)
- [ ] Implementar listener de teclado (WASD e ZQSD)
- [ ] Função `try_move(dx, dy)`:
  - Testa colisão com parede
  - Atualiza coordenadas se válido
- **🎯 Meta:** Movimentação básica funciona
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: player movement"`

#### 🔢 Bloco 2 (50 min)
- [ ] Incrementar contador ao mover
- [ ] Imprimir no terminal: `Moves: X`
- **🎯 Meta:** Contador correto
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: increment move count"`

#### 💎 Bloco 3 (50 min)
- [ ] Detectar coletáveis (`C`) ao entrar na célula
- [ ] Remover `C` da matriz
- [ ] Decrementar total de coletáveis
- [ ] (Opcional: som ao coletar)
- **🎯 Meta:** Coletáveis desaparecem
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: collect items"`

#### 🚪 Bloco 4 (50 min)
- [ ] Lógica da saída (`E`):
  - Se ainda há coletáveis → bloquear + mensagem
  - Se coletou tudo → encerrar com sucesso
- [ ] Exit limpo (liberar memória)
- **🎯 Meta:** Saída implementada
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: exit logic"`

---

### ✅ Checklist do Dia 7 (5h) — Testes + Robustez

#### 🧪 Bloco 1 (50 min)
- [ ] Criar mapas de teste:
  - Movimento bloqueado por paredes
  - Todos coletáveis acessíveis
  - Sequência longa de movimentos
- **🎯 Meta:** Suite de testes atualizada
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "test: movement & collect maps"`

#### 🛡️ Bloco 2 (50 min)
- [ ] Testar bordas do mapa
- [ ] Movimentos rápidos (spam de teclas)
- [ ] Minimizar/restaurar janela
- [ ] Trocar de janela
- [ ] Garantir que não crasha
- **🎯 Meta:** Event handling robusto
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "fix: event handling"`

#### 🧹 Bloco 3 (50 min)
- [ ] Rodar valgrind (se disponível)
- [ ] Checar memory leaks
- [ ] Corrigir vazamentos encontrados
- **🎯 Meta:** Memória liberada corretamente
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "test: memory checks"`

#### 📸 Bloco 4 (50 min)
- [ ] Gravar demo curto (GIF/vídeo)
- [ ] Ou tirar prints para README
- [ ] Documentar controles
- **🎯 Meta:** Demo pronta
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "docs: demo images"`

### 🏆 **Critério de Aceitação:**
✅ Jogador se move corretamente (WASD/ZQSD)  
✅ Coleta itens e contador atualiza  
✅ Sai apenas quando coletou tudo  
✅ Sem segfaults ou crashes

---

## 🐱 **FASE 4** — Inimigo (Ozzy) e lógica de perda (BÔNUS)
**⏱️ Tempo:** 2–3 dias (recomendado 3)  
**🎯 Objetivo:** Ozzy persegue Louis, causa game over ao colidir, animações básicas

### ✅ Checklist do Dia 8 (5h) — AI Básico

#### 👾 Bloco 1 (50 min)
- [ ] Adicionar entidade Ozzy
- [ ] Definir posição inicial no mapa
- [ ] Renderizar sprite do Ozzy
- **🎯 Meta:** Ozzy visível no mapa
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: add enemy entity"`

#### 🧠 Bloco 2 (50 min)
- [ ] Implementar movimento simples:
  - A cada N frames, Ozzy se move
  - Algoritmo greedy: priorizar eixo com maior diferença até Louis
  - Evitar paredes
- **🎯 Meta:** Ozzy persegue de forma previsível
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: basic chase AI"`

#### 💀 Bloco 3 (50 min)
- [ ] Detectar colisão Louis ↔ Ozzy
- [ ] Imprimir `You lose!`
- [ ] Exit limpo (liberar memória)
- **🎯 Meta:** Game over implementado
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: player death on collision"`

#### ⚙️ Bloco 4 (50 min)
- [ ] Testar com diferentes mapas
- [ ] Ajustar velocidade do Ozzy
- [ ] Balancear dificuldade
- **🎯 Meta:** Dificuldade ajustável
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "test: enemy tuning"`

---

### ✅ Checklist do Dia 9 (5h) — Animação + Polimento

#### 🎬 Bloco 1 (50 min)
- [ ] Implementar sprite sheet básico
- [ ] Timer para trocar frames
- [ ] Animação para Louis
- [ ] Animação para Ozzy
- **🎯 Meta:** Animações básicas funcionando
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: sprite animation"`

#### 📊 Bloco 2 (50 min)
- [ ] (Opcional) Mostrar contador na janela
- [ ] Desenhar texto com MinilibX
- [ ] Posicionar HUD (ex: canto superior)
- **🎯 Meta:** Move count on-screen
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "feat: moves displayed in-window"`

#### 🔧 Bloco 3 (50 min)
- [ ] Ajustar performance das animações
- [ ] Limpar código
- [ ] Preparar fallback se animação travar
- **🎯 Meta:** Animação estável
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "fix: animation stability"`

#### 🎮 Bloco 4 (50 min)
- [ ] Playtest final com inimigo
- [ ] Ajustar mapa se necessário
- [ ] Testar diferentes cenários
- **🎯 Meta:** Playtest concluído
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "test: enemy & animation playtest"`

### 🏆 **Critério de Aceitação:**
✅ Ozzy persegue Louis  
✅ Colisão causa game over  
✅ Animações suaves  
✅ (Opcional) Contador na janela

---

## 🏁 **FASE 5** — Polimento, documentação e submissão
**⏱️ Tempo:** 1–2 dias  
**🎯 Objetivo:** Bugs corrigidos, README completo, projeto pronto para entregar

### ✅ Checklist do Dia 10 (5h) — Finalização

#### 🐛 Bloco 1 (50 min)
- [ ] Corrigir issues menores
- [ ] Revisar mensagens de erro:
  - Formato: `Error\n<mensagem>`
- [ ] Padronizar output
- **🎯 Meta:** Mensagens padronizadas
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "chore: standardize errors"`

#### 📖 Bloco 2 (50 min)
- [ ] Escrever README detalhado:
  - ✅ Como compilar
  - ✅ Como executar
  - ✅ Controles (WASD/ZQSD, ESC)
  - ✅ Créditos de sprites/assets
- **🎯 Meta:** README completo
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "docs: add README"`

#### 📦 Bloco 3 (50 min)
- [ ] Organizar pasta `assets/` com sprites finais
- [ ] Preparar mapas finais em `maps/`
- [ ] Verificar estrutura de pastas
- **🎯 Meta:** Pacote pronto para submissão
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "chore: assets & final maps"`

#### ✅ Bloco 4 (50 min)
- [ ] Rodar `make fclean`
- [ ] Rodar `make` (compilação limpa)
- [ ] Testar tudo uma última vez
- [ ] Criar tag/branch final
- **🎯 Meta:** Build final OK
- **⏸️ PAUSA 10 min** → 💾 `git commit -m "release: final submission"`

### 🏆 **Critério de Aceitação:**
✅ Projeto compila do zero (`make fclean && make`)  
✅ README claro e completo  
✅ Mapas e assets organizados  
✅ Pronto para submissão

---

## 🎯 **RESUMO RÁPIDO**

| Fase | Tempo | Foco Principal |
|------|-------|----------------|
| 0️⃣ | 1 dia | Setup, Makefile, MinilibX |
| 1️⃣ | 2-3 dias | Parser + validações |
| 2️⃣ | 2 dias | Renderização + sprites |
| 3️⃣ | 2 dias | Movimento + coleta |
| 4️⃣ | 2-3 dias | Inimigo + animação (BÔNUS) |
| 5️⃣ | 1-2 dias | Polimento + docs |

**⏱️ Total:** 10-13 dias

---

## 💡 **DICAS PARA TDAH**

- ✅ **Respeite as pausas de 10 min** — essenciais para manter o foco
- ✅ **Commits pequenos e frequentes** — sensação de progresso constante
- ✅ **Um bloco de cada vez** — não pule etapas
- ✅ **Use timers** — Pomodoro ajuda muito
- ✅ **Celebre cada checkbox** — você tá arrasando! 🎉
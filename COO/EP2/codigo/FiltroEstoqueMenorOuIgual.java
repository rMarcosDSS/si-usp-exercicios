public class FiltroEstoqueMenorOuIgual implements FiltroStrategy {
    private int limite;

    public FiltroEstoqueMenorOuIgual(int limite) {
        this.limite = limite;
    }

    @Override
    public boolean filtra(Produto produto) {
        return produto.getQtdEstoque() <= limite;
    }
}
public class FiltroPrecoIntervalo implements FiltroStrategy {
    private double min;
    private double max;

    public FiltroPrecoIntervalo(double min, double max) {
        this.min = min;
        this.max = max;
    }

    @Override
    public boolean filtra(Produto produto) {
        return produto.getPreco() >= min && produto.getPreco() <= max;
    }
}
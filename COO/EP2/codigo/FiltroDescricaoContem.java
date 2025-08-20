public class FiltroDescricaoContem implements FiltroStrategy {
    private String substring;

    public FiltroDescricaoContem(String substring) {
        this.substring = substring;
    }

    @Override
    public boolean filtra(Produto produto) {
        return produto.getDescricao().toLowerCase().contains(substring.toLowerCase());
    }
}
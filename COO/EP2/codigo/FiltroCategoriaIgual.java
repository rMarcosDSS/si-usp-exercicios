public class FiltroCategoriaIgual implements FiltroStrategy {
    private String categoria;

    public FiltroCategoriaIgual(String categoria) {
        this.categoria = categoria;
    }

    @Override
    public boolean filtra(Produto produto) {
        return produto.getCategoria().equalsIgnoreCase(categoria);
    }
}
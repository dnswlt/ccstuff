autoload=~/.vim/autoload
bundle=~/.vim/bundle

if [ -f $autoload/pathogen.vim ]; then
  echo "Pathogen already installed. Aborting."
  exit 1
fi

echo "Installing pathogen"
mkdir -p $bundle $autoload
curl -LSso $autoload/pathogen.vim https://tpo.pe/pathogen.vim

echo "Installing CtrlP"
git clone https://github.com/kien/ctrlp.vim.git $bundle/ctrlp.vim

echo "Installing ack.vim"
git clone https://github.com/mileszs/ack.vim.git $bundle/ack.vim

# Uncomment if you want gruvbox. Maybe not so useful when using vim from the console.
# echo "Installing gruvbox"
# git clone https://github.com/morhetz/gruvbox.git ~/.vim/bundle/gruvbox

echo "Adding source directive to .vimrc"
me=$(realpath $0)
echo "\" Added by $(basename $me)" >> ~/.vimrc
echo source $(dirname $me)/.vimrc >> ~/.vimrc


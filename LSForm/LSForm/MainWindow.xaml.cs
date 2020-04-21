using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace LSForm
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            var TopMenuItems = new ObservableCollection<MenuItem>
            {
                new MenuItem
                {
                    Header = "File",
                    Items = {
                        new MenuItem
                        {
                            Header = "New"
                        },
                        new MenuItem
                        {
                            Header = "Open"
                        },
                        new MenuItem
                        {
                            Header = "Save"
                        }
                    }
                },
                new MenuItem
                {
                    Header = "Edit"
                },
                new MenuItem
                {
                    Header = "Search"
                }
            };

            ReadyTemplates.ItemsSource = TopMenuItems;
        }
    }
}
